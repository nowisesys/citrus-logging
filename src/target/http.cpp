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

#ifdef HAVE_LIBCURL
#include <curl/curl.h>

namespace {
        static int init;
}

namespace Citrus::Logging {

        TargetHttp::TargetHttp(const std::string & url, const Format & format)
            : Target(format), curl(nullptr), headers(nullptr)
        {
                CURLcode res;

                if (init++ == 0) {
                        if (curl_global_init(CURL_GLOBAL_ALL)) {
                                throw NetworkException("Failed initialize cURL");
                        }
                }

                if ((curl = curl_easy_init()) == 0) {
                        throw NetworkException("Failed initialize cURL");
                }

                if ((res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())) != 0) {
                        throw NetworkException("Failed set CURLOPT_URL", curl_easy_strerror(res));
                }
                if ((res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L)) != 0) {
                        throw NetworkException("Failed set CURLOPT_POSTFIELDSIZE", curl_easy_strerror(res));
                }

#if defined(LIBCURL_PROTOCOL_HTTPS)
                if ((res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 2)) != 0) {
                        throw NetworkException("Failed set CURLOPT_SSL_VERIFYPEER", curl_easy_strerror(res));
                }
                if ((res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2)) != 0) {
                        throw NetworkException("Failed set CURLOPT_SSL_VERIFYHOST", curl_easy_strerror(res));
                }
#endif
        }

        TargetHttp::~TargetHttp()
        {
                if (curl) {
                        curl_easy_cleanup(curl);
                }
                if (--init == 0) {
                        curl_global_cleanup();
                }
                if (headers) {
                        curl_slist_free_all(headers);
                }
        }

        void TargetHttp::Append(const Record & record) const
        {
                const std::string & message = format.GetMessage(record);

                if (CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); res != 0) {
                        throw NetworkException("Failed set headers", curl_easy_strerror(res));
                }
                if (CURLcode res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message.c_str()); res != 0) {
                        throw NetworkException("Failed set CURLOPT_POSTFIELDS", curl_easy_strerror(res));
                }
                if (CURLcode res = curl_easy_perform(curl); res != 0) {
                        throw NetworkException("Failed send request", curl_easy_strerror(res));
                }
        }

        void TargetHttp::SetOption(CURLoption option, long value) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, value); res != 0) {
                        throw NetworkException("Failed set option", curl_easy_strerror(res));
                }
        }

        void TargetHttp::SetOption(CURLoption option, const std::string & value) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, value.c_str()); res != 0) {
                        throw NetworkException("Failed set option", curl_easy_strerror(res));
                }
        }

        void TargetHttp::AddHeader(const char * name, const char * value)
        {
                AddHeader(std::string(name) + ": " + std::string(value));
        }

        void TargetHttp::AddHeader(const std::string & header)
        {
                curl_slist * temp = curl_slist_append(headers, header.c_str());

                if (!temp) {
                        throw NetworkException("Failed set HTTP header", header.c_str());
                }

                headers = temp;
        }

        void TargetHttp::SetLogin(const char * user, const char * pass) const
        {
                if (CURLcode res = curl_easy_setopt(curl, CURLOPT_USERNAME, user); res != 0) {
                        throw NetworkException("Failed set login username", curl_easy_strerror(res));
                }
                if (CURLcode res = curl_easy_setopt(curl, CURLOPT_PASSWORD, pass); res != 0) {
                        throw NetworkException("Failed set login password", curl_easy_strerror(res));
                }
        }

} // namespace Citrus::Logging

#endif // HAVE_LIBCURL
