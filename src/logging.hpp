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

#ifndef LIBCITRUS_LOGGING_HPP
#define LIBCITRUS_LOGGING_HPP

#include <any>
#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#endif

#ifdef HAVE_LIBCURL
#include <curl/curl.h>
#endif

namespace Citrus::Logging {

        using Arguments = std::vector<std::any>;

        class CurlHandle;
        class CurlStringList;

        class InvalidArgumentException : public std::invalid_argument
        {
            public:
                template <typename T>
                InvalidArgumentException(std::string msg, T t)
                    : std::invalid_argument(msg + ": " + t) {}
                InvalidArgumentException(const char * msg)
                    : std::invalid_argument(msg) {}
        };

        class FileSystemException : public std::runtime_error
        {
            public:
                FileSystemException(std::string msg, const char * path)
                    : std::runtime_error(msg + ": " + path) {}
                FileSystemException(const char * msg)
                    : std::runtime_error(msg) {}
        };

        class NetworkException : public std::runtime_error
        {
            public:
                NetworkException(std::string msg, const char * error)
                    : std::runtime_error(msg + ": " + error) {}
                NetworkException(const char * msg)
                    : std::runtime_error(msg) {}
        };

        enum class Level
        {
                Debug,       // Debug level message
                Information, // Informational message
                Notice,      // Normal, but significant, condition
                Warning,     // Warning conditions
                Error,       // Error conditions
                Critical,    // Critical conditions
                Alert,       // Action must be taken immediately
                Emergent     // System is unusable
        };

        class DateTime
        {
            public:
                using TimePoint = std::chrono::system_clock::time_point;
                using TimeClock = std::chrono::system_clock;

                struct Format
                {
                        static const char * Human;
                        static const char * Database;
                        static const char * Locale;
                        static const char * Epoch;
                        static const char * Timezone;
                        static const char * ISO8601;
                };

                explicit DateTime();
                DateTime(const char * format);
                DateTime(const char * format, const TimePoint & stamp);
                DateTime(const TimePoint & stamp);

                void SetFormat(const char * format);
                void SetTimeZone(const char * timezone);
                void SetTimePoint(const TimePoint & stamp);

                const char * GetFormat() const;
                const char * GetTimeZone() const;
                const TimePoint & GetTimePoint() const;

                std::string GetString() const;
                std::string GetString(const char * format) const;

                static DateTime Now(const char * format = Format::Human);

            private:
                const char * format;
                TimePoint stamp;
        };

        class Hostname
        {
            public:
                Hostname();

                const std::string GetQualified() const;
                std::string GetDomain() const;
                std::string GetShort() const;

                static const Hostname & GetInstance();

            private:
                std::string hostname;
        };

        class Format;
        class Record
        {
            public:
                Record();
                Record(const std::string & message);
                Record(Level priority, const std::string & message);
                Record(Level priority, const std::string & ident, const std::string & message);

                void SetPriority(Level priority);
                void SetIdentity(const std::string & ident);
                void SetMessage(const std::string & message);

                Level GetPriority() const;
                std::string GetSeverity() const; // Get priority as string
                const std::string & GetIdentity() const;
                const std::string & GetMessage() const;
                int GetProcess() const;
                const DateTime & GetDateTime() const;
                const Hostname & GetHostname() const;

            private:
                void SetProcess();

                Level priority;
                std::string ident;
                std::string message;
                int pid;
                DateTime stamp;
        };

        class Format
        {
            public:
                virtual std::string GetMessage(const Record & record) const = 0;
                static std::string GetSeverity(Level level);
        };

        class Target
        {
            public:
                virtual ~Target() = default;
                virtual void Append(const Record & record) const = 0;
                virtual void Append(const std::vector<Record> & records) const;

            protected:
                Target(const Format & format);
                const Format & format;
        };

        class Message
        {
            public:
                static std::string Format(const char * format, const Arguments & args = Arguments());
                static std::string Format(const std::string & format, const Arguments & args = Arguments());
        };

        class Sender
        {
            public:
                void Register(Target * target);
                void Register(Target * target, Level level);
                void Register(Target * target, Level lower, Level upper);

                void Write(Level priority, const std::string & message) const;
                void Write(Level priority, const std::string & ident, const std::string & message) const;
                void Write(const Record & record) const;

            private:
                std::map<Level, std::vector<Target *>> targets;
        };

        class Logger
        {
            public:
                Logger() : threshold(Level::Information) {}
                Logger(Level level) : threshold(level) {}

                void SetIdentity(const std::string & ident);
                void SetThreshold(Level level);

                Sender & GetSender();
                const Sender & GetSender() const;

                void Message(Level level, const char * format, const Arguments & args = Arguments()) const;
                void Emergent(const char * format, const Arguments & args = Arguments()) const;
                void Alert(const char * format, const Arguments & args = Arguments()) const;
                void Critical(const char * format, const Arguments & args = Arguments()) const;
                void Error(const char * format, const Arguments & args = Arguments()) const;
                void Warning(const char * format, const Arguments & args = Arguments()) const;
                void Notice(const char * format, const Arguments & args = Arguments()) const;
                void Information(const char * format, const Arguments & args = Arguments()) const;
                void Debug(const char * format, const Arguments & args = Arguments()) const;

                void operator()(Level level, const char * format) const;
                void operator()(Level level, const char * format, const Arguments & args) const;

                bool IsFiltered(Level level) const;

            private:
                Sender sender;
                Level threshold;
                std::string ident;
        };

        class FormatZero : public Format
        {
            public:
                std::string GetMessage(const Record & record) const override;
        };

        class FormatText : public Format
        {
            public:
                FormatText(char field = '\t', char lines = '\n');
                std::string GetMessage(const Record & record) const override;

            private:
                char field;
                char lines;
        };

        class FormatJson : public Format
        {
            public:
                FormatJson(bool pretty = false);
                std::string GetMessage(const Record & record) const override;

            private:
                bool pretty;
        };

        class FormatXml : public Format
        {
            public:
                FormatXml(bool pretty = false, bool attrib = true);
                std::string GetMessage(const Record & record) const override;

            private:
                bool pretty;
                bool attrib;
        };

        class FormatCsv : public Format
        {
            public:
                FormatCsv(char delimit = ',', char enclose = '"', char escape = '\\');
                std::string GetMessage(const Record & record) const override;

            private:
                char delimit;
                char enclose;
                char escape;
        };

        class FormatSql : public Format
        {
            public:
                FormatSql();
                FormatSql(const std::string & table);
                FormatSql(const std::string & table, const std::map<std::string, std::string> & columns);

                std::string GetMessage(const Record & record) const override;

            private:
                std::string table;
                std::map<std::string, std::string> columns;
        };

        class FormatPrefix : public Format
        {
            public:
                enum class Mapping
                {
                        Default,   // i.e. "Error: Text message"
                        LowerCase, // i.e. "error: Text message"
                        UpperCase, // i.e. "ERROR: Text message"
                        ShortTag   // i.e. "[e]: Text message
                };

                FormatPrefix();
                FormatPrefix(Mapping mapping);
                FormatPrefix(const std::map<Level, std::string> & mapping);

                std::string GetMessage(const Record & record) const override;

            private:
                std::map<Level, std::string> mapping;
        };

        class FormatUser : public Format
        {
            public:
                FormatUser(const std::function<std::string(const Record & record)> & formatter);
                std::string GetMessage(const Record & record) const override;

            private:
                const std::function<std::string(const Record & record)> & formatter;
        };

        class FormatColumn : public Format
        {
            public:
                FormatColumn(char field = ':', char lines = '\n');
                std::string GetMessage(const Record & record) const override;

            private:
                char field;
                char lines;
        };

        class FormatString : public Format
        {
            public:
                FormatString(const std::string & format); // %1 -> datetime, %2 -> hostname, %3 -> identity, %4 -> message, %5 -> priority, %6 -> process
                std::string GetMessage(const Record & record) const override;

            private:
                std::string format;
        };

        template <class Format, typename... Params>
        struct RecordFormat
        {
                static Format & Object(Params... args)
                {
                        static Format format(args...);
                        return format;
                }
        };

        class TargetFile : public Target
        {
            public:
                TargetFile(const char * filename, const Format & format = RecordFormat<FormatText>::Object());
                void Append(const Record & record) const override;
                void Append(const std::vector<Record> & records) const;

            private:
                std::string filename;
        };

        class TargetStream : public Target
        {
            public:
                TargetStream(std::ostream & stream, const Format & format = RecordFormat<FormatText>::Object());
                void Append(const Record & record) const override;

            private:
                std::ostream & stream;
        };

#if defined(HAVE_SYSLOG_H)
        class TargetSyslog : public Target
        {
            public:
                TargetSyslog(const char * ident, const Format & format);
                TargetSyslog(const char * ident, int option = LOG_CONS | LOG_PID, int facility = LOG_DAEMON, const Format & format = RecordFormat<FormatZero>::Object());
                ~TargetSyslog();

                void Append(const Record & record) const override;
        };
#endif

#if defined(HAVE_LIBCURL) && defined(LIBCURL_PROTOCOL_HTTP)
        class TargetHttp : public Target
        {
            public:
                TargetHttp(const std::string & url, const Format & format = RecordFormat<FormatJson>::Object());
                ~TargetHttp();

                void Append(const Record & record) const override;

                void SetOption(CURLoption option, long value) const;
                void SetOption(CURLoption option, const std::string & value) const;

                void AddHeader(const char * name, const char * value);
                void AddHeader(const std::string & value);

                void SetLogin(const char * user, const char * pass) const;

            private:
                CurlHandle * chandle;
                CurlStringList * headers;
        };
#endif

#if defined(HAVE_LIBCURL) && defined(LIBCURL_PROTOCOL_SMTP)
        class TargetSmtp : public Target
        {
            public:
                struct Address
                {
                        Address() = default;
                        Address(const Address &) = default;
                        Address(const std::string & addr, const std::string & name)
                            : addr(addr), name(name) {}

                        operator std::string() const
                        {
                                return name + " <" + addr + ">";
                        }

                        std::string addr;
                        std::string name;
                };

                class Sender;
                class Message
                {
                        friend class Sender;

                    public:
                        explicit Message() = default;
                        explicit Message(const Message &) = default;

                        Message(const Address & sender, const Address & recipient, const std::string & subject);

                        void SetSubject(const std::string & subject);
                        void SetBodyText(const std::string & text);

                        void SetSender(const Address & sender);
                        void SetSender(const std::string & addr, const std::string & name = "");

                        void AddRecipient(const Address & recipient);
                        void AddRecipient(const std::string & addr, const std::string & name = "");

                        void SetRecipients(const Address & recipient);                               // Replace all
                        void SetRecipients(const std::string & addr, const std::string & name = ""); // Replace all
                        void SetRecipients(const std::vector<Address> & recipients);                 // Replace all

                        void AddHeader(const char * name, const char * value);
                        void AddHeader(const std::string & value);

                        std::string GetFormatted(const std::string & body) const;
                        std::string GetFormatted() const;
                        std::string GetMessageID() const;

                    private:
                        std::string GetDomain() const;
                        std::string GetNextUuid() const;

                        std::string GetCopyReceivers() const;

                        Address sender;
                        std::string subject;
                        std::string body;
                        std::vector<Address> recipients;
                        std::vector<std::string> headers;
                };

                class Sender
                {
                    public:
                        Sender(const CurlHandle * handle);
                        void Submit(const Message & message) const;
                        void Submit(const Message & message, const std::string & text) const;

                    private:
                        static size_t Upload(char * buffer, size_t size, size_t nitems, void * userdata);
                        const CurlHandle * chandle;
                };

                TargetSmtp(const std::string & url, const Format & format = RecordFormat<FormatColumn>::Object());
                TargetSmtp(const std::string & url, const Message & message, const Format & format = RecordFormat<FormatColumn>::Object());
                ~TargetSmtp();

                void Append(const Record & record) const override;

                void SetOption(CURLoption option, long value) const;
                void SetOption(CURLoption option, const std::string & value) const;

                void SetLogin(const char * user, const char * pass) const;

                Message * GetMessage();

            private:
                CurlHandle * chandle;
                Message message;
        };
#endif

        class TargetDiscard : public Target
        {
                void Append(const Record & record) const override {}
        };

        class MemoryStrategy;
        class TargetMemory : public Target
        {
            public:
                using Callback = std::function<void(const MemoryStrategy *)>;
                using size_type = std::vector<Record>::size_type;

                TargetMemory(int size = 25);
                TargetMemory(Callback callback, int size = 25);
                TargetMemory(MemoryStrategy * strategy); // This object takes ownership of strategy
                TargetMemory(const TargetMemory & other);
                TargetMemory(TargetMemory && other) noexcept;
                ~TargetMemory();

                TargetMemory & operator=(const TargetMemory & other);
                TargetMemory & operator=(TargetMemory && other) noexcept;

                void Append(const Record & record) const override;

                MemoryStrategy * GetMemoryStrategy();

            private:
                MemoryStrategy * strategy;
        };

        class MemoryStrategy
        {
            public:
                using Callback = TargetMemory::Callback;
                using size_type = TargetMemory::size_type;

                explicit MemoryStrategy();
                
                MemoryStrategy(const MemoryStrategy &) = default;
                virtual ~MemoryStrategy() = default;

                void OnOverflow(Callback callback);

                virtual void Append(const Record & record) = 0;
                virtual std::vector<Record> GetBuffer() const = 0;
                virtual std::vector<Record> GetLatest() const = 0; // Since last overflow

                virtual MemoryStrategy * Clone() const noexcept = 0;

            protected:
                std::vector<Record> buffer;
                Callback callback;
        };

        class MemoryStrategyGrowing : public MemoryStrategy
        {
            public:
                MemoryStrategyGrowing(size_type size = 25);
                MemoryStrategyGrowing(Callback callback, size_type size = 25);
                ~MemoryStrategyGrowing();

                void Append(const Record & record) override;
                std::vector<Record> GetBuffer() const override;
                std::vector<Record> GetLatest() const override;

                MemoryStrategy * Clone() const noexcept override
                {
                        return new MemoryStrategyGrowing(*this);
                }

            private:
                size_type size;
                size_type last;
        };

        class MemoryStrategyLinear : public MemoryStrategy
        {
            public:
                MemoryStrategyLinear(size_type size = 25);
                MemoryStrategyLinear(Callback callback, size_type size = 25);
                ~MemoryStrategyLinear();

                void Append(const Record & record) override;
                std::vector<Record> GetBuffer() const override;
                std::vector<Record> GetLatest() const override;

                MemoryStrategy * Clone() const noexcept override
                {
                        return new MemoryStrategyLinear(*this);
                }

            private:
                size_type size;
        };

        class MemoryStrategyCircular : public MemoryStrategy
        {
            public:
                MemoryStrategyCircular(size_type size = 25);
                MemoryStrategyCircular(Callback callback, size_type size = 25);
                ~MemoryStrategyCircular();

                void Append(const Record & record) override;
                std::vector<Record> GetBuffer() const override;
                std::vector<Record> GetLatest() const override;

                MemoryStrategy * Clone() const noexcept override
                {
                        return new MemoryStrategyCircular(*this);
                }

            private:
                size_type size;
                size_type curr;
        };

        class TargetBuffer : public TargetMemory
        {
            public:
                using size_type = TargetMemory::size_type;

                TargetBuffer(const Target & target);
                TargetBuffer(const Target & target, size_type size);
                TargetBuffer(const Target & target, MemoryStrategy * strategy);

                void operator()(const MemoryStrategy * strategy);

            private:
                const Target & target;
        };

} // namespace Citrus::Logging

#endif // LIBCITRUS_LOGGING_HPP
