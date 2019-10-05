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

#ifndef LIBCITRUS_UTILS_CURL_HPP
#define LIBCITRUS_UTILS_CURL_HPP

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBCURL

#include <string>
#include <vector>

#include <curl/curl.h>

namespace Citrus::Logging {

        class CurlHandle
        {
            public:
                typedef size_t Callback(char * buffer, size_t size, size_t nitems, void * userdata);

                CurlHandle();
                CurlHandle(const std::string & url);
                ~CurlHandle();

                operator CURL *()
                {
                        return curl;
                }

                void SetOption(CURLoption option, long value) const;
                void SetOption(CURLoption option, const std::string & value) const;
                void SetOption(CURLoption option, Callback callback) const;
                void SetOption(CURLoption option, void * object) const;

                void Perform() const;

            private:
                CURL * curl;
        };

        class CurlStringList
        {
            public:
                CurlStringList();
                CurlStringList(const char * value);
                CurlStringList(const std::string & value);
                CurlStringList(const std::vector<const char *> & values);
                ~CurlStringList();

                operator curl_slist *()
                {
                        return list;
                }

                void Append(const char * value);
                void Append(const std::string & value);

                template <typename T>
                void Append(const T & value)
                {
                        Append(std::to_string(value).c_str());
                }

            private:
                curl_slist * list;
        };

} // namespace Citrus::Logging

#endif // HAVE_LIBCURL
#endif // LIBCITRUS_UTILS_CURL_HPP
