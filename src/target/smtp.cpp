// Copyright (C) 2019 Anders Lövgren (Nowise Systems)
//
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logging.hpp"
#include "utils/curl.hpp"
#include "utils/uuid.hpp"

#include <sstream>

#ifdef HAVE_LIBCURL

namespace {

        class StringData
        {
            public:
                std::string buffer;
                size_t remain;

                StringData(std::string & buffer) = delete;
                StringData(std::string && buffer)
                    : buffer(buffer), remain(buffer.size()) {}
        };

} // namespace

namespace Citrus::Logging {

        TargetSmtp::TargetSmtp(const std::string & url, const Format & format)
            : Target(format)
        {
                chandle = new CurlHandle(url);
        }

        TargetSmtp::TargetSmtp(const std::string & url, const Message & message, const Format & format)
            : Target(format), message(message)
        {
                chandle = new CurlHandle(url);
        }

        TargetSmtp::~TargetSmtp()
        {
                delete chandle;
        }

        void TargetSmtp::Append(const Record & record) const
        {
                const std::string & text = format.GetMessage(record);

                Sender sender(chandle);
                sender.Submit(message, text);
        }

        void TargetSmtp::SetOption(CURLoption option, long value) const
        {
                chandle->SetOption(option, value);
        }

        void TargetSmtp::SetOption(CURLoption option, const std::string & value) const
        {
                chandle->SetOption(option, value);
        }

        void TargetSmtp::SetLogin(const char * user, const char * pass) const
        {
                chandle->SetOption(CURLOPT_USERNAME, user);
                chandle->SetOption(CURLOPT_PASSWORD, pass);
        }

        TargetSmtp::Message * TargetSmtp::GetMessage()
        {
                return &message;
        }

        TargetSmtp::Message::Message(const Address & sender, const Address & recipient, const std::string & subject)
            : sender(sender), subject(subject)
        {
                this->recipients.push_back(recipient);
        }

        void TargetSmtp::Message::SetSubject(const std::string & subject)
        {
                this->subject = subject;
        }

        void TargetSmtp::Message::SetBodyText(const std::string & text)
        {
                this->body = text;
        }

        void TargetSmtp::Message::SetSender(const Address & sender)
        {
                this->sender = sender;
        }

        void TargetSmtp::Message::SetSender(const std::string & addr, const std::string & name)
        {
                this->sender = Address(addr, name);
        }

        void TargetSmtp::Message::AddRecipient(const Address & recipient)
        {
                this->recipients.push_back(recipient);
        }

        void TargetSmtp::Message::AddRecipient(const std::string & addr, const std::string & name)
        {
                this->recipients.push_back(Address(addr, name));
        }

        void TargetSmtp::Message::SetRecipients(const Address & recipient)
        {
                this->recipients.clear();
                this->recipients.push_back(recipient);
        }

        void TargetSmtp::Message::SetRecipients(const std::string & addr, const std::string & name)
        {
                this->recipients.clear();
                this->recipients.push_back(Address(addr, name));
        }

        void TargetSmtp::Message::SetRecipients(const std::vector<Address> & recipients)
        {
                this->recipients = recipients;
        }

        void TargetSmtp::Message::AddHeader(const char * name, const char * value)
        {
                headers.push_back((std::string(name) + ": " + std::string(value)));
        }

        void TargetSmtp::Message::AddHeader(const std::string & value)
        {
                headers.push_back(value);
        }

        std::string TargetSmtp::Message::GetFormatted(const std::string & body) const
        {
                if (recipients.empty()) {
                        throw NetworkException("The list of recipients (To and Cc) is empty");
                }

                std::ostringstream oss;

                oss << "Date: " << DateTime::Now().GetString() << "\r\n";
                if (recipients.size()) {
                        oss << "To: " << static_cast<const std::string &>(recipients[0]) << "\r\n";
                }
                if (sender.addr.length()) {
                        oss << "From: " << static_cast<const std::string &>(sender) << "\r\n";
                }
                if (recipients.size() > 1) {
                        oss << "Cc: " << GetCopyReceivers() << "\r\n";
                }

                for (const std::string & header : headers) {
                        oss << header << "\r\n";
                }

                oss << "Message-ID: " << GetMessageID() << "\r\n"
                    << "Subject: " << subject << "\r\n"
                    << "\r\n"
                    << body << "\r\n";

                return oss.str();
        }

        std::string TargetSmtp::Message::GetFormatted() const
        {
                return GetFormatted(body);
        }

        std::string TargetSmtp::Message::GetMessageID() const
        {
                return GetNextUuid() + '@' + GetDomain();
        }

        std::string TargetSmtp::Message::GetDomain() const
        {
                return sender.addr.substr(sender.addr.find('@') + 1);
        }

        std::string TargetSmtp::Message::GetNextUuid() const
        {
                return UuidGenerator::Next();
        }

        std::string TargetSmtp::Message::GetCopyReceivers() const
        {
                const std::vector<Address> & copies = std::vector<Address>(recipients.begin() + 1, recipients.end());
                std::string result;

                for (auto & copy : copies) {
                        result += static_cast<const std::string &>(copy) + ", ";
                }

                return result.substr(0, result.length() - 2);
        }

        TargetSmtp::Sender::Sender(const CurlHandle * chandle)
            : chandle(chandle)
        {
        }

        void TargetSmtp::Sender::Submit(const Message & message) const
        {
                Submit(message, message.body);
        }

        void TargetSmtp::Sender::Submit(const Message & message, const std::string & text) const
        {
                StringData data(message.GetFormatted(text));
                CurlStringList recipients;

                for (auto recipient : message.recipients) {
                        recipients.Append(recipient.addr);
                }

                chandle->SetOption(CURLOPT_MAIL_FROM, message.sender.addr);
                chandle->SetOption(CURLOPT_MAIL_RCPT, recipients);

                chandle->SetOption(CURLOPT_READFUNCTION, Upload);
                chandle->SetOption(CURLOPT_READDATA, &data);
                chandle->SetOption(CURLOPT_UPLOAD, 1L);

                chandle->Perform();
        }

        size_t TargetSmtp::Sender::Upload(char * buffer, size_t size, size_t nitems, void * userdata)
        {
                StringData * text = reinterpret_cast<StringData *>(userdata);

                if ((size == 0) || (nitems == 0) || ((size * nitems) < 1) || (text->remain == 0)) {
                        return 0;
                }

                if ((nitems * size) >= text->buffer.size()) {
                        text->remain = 0;
                        return text->buffer.copy(reinterpret_cast<char *>(buffer), text->buffer.size());
                }

                return 0;
        }

} // namespace Citrus::Logging

#endif // HAVE_LIBCURL
