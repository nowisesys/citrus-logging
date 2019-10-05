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

#ifdef HAVE_LIBCURL

namespace {
        static int init;
}

namespace Citrus::Logging {

        TargetHttp::TargetHttp(const std::string & url, const Format & format)
            : Target(format)
        {
                chandle = new CurlHandle(url);
                headers = new CurlStringList();

                chandle->SetOption(CURLOPT_POSTFIELDSIZE, -1L);

#if defined(LIBCURL_PROTOCOL_HTTPS)
                chandle->SetOption(CURLOPT_SSL_VERIFYPEER, 2L);
                chandle->SetOption(CURLOPT_SSL_VERIFYHOST, 2L);
#endif
        }

        TargetHttp::~TargetHttp()
        {
                delete headers;
                delete chandle;
        }

        void TargetHttp::Append(const Record & record) const
        {
                const std::string & message = format.GetMessage(record);

                chandle->SetOption(CURLOPT_HTTPHEADER, headers->GetList());
                chandle->SetOption(CURLOPT_POSTFIELDS, message);
                chandle->Perform();
        }

        void TargetHttp::SetOption(CURLoption option, long value) const
        {
                chandle->SetOption(option, value);
        }

        void TargetHttp::SetOption(CURLoption option, const std::string & value) const
        {
                chandle->SetOption(option, value);
        }

        void TargetHttp::AddHeader(const char * name, const char * value)
        {
                AddHeader(std::string(name) + ": " + std::string(value));
        }

        void TargetHttp::AddHeader(const std::string & header)
        {
                headers->Append(header.c_str());
        }

        void TargetHttp::SetLogin(const char * user, const char * pass) const
        {
                chandle->SetOption(CURLOPT_USERNAME, user);
                chandle->SetOption(CURLOPT_PASSWORD, pass);
        }

} // namespace Citrus::Logging

#endif // HAVE_LIBCURL
