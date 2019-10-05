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

#ifdef HAVE_LIBCURL

#include "curl.hpp"
#include "logging.hpp"

#include <curl/curl.h>

namespace {

        static int init;
}

namespace Citrus::Logging {

        CurlHandle::CurlHandle()
            : curl(nullptr)
        {
                if (init++ == 0) {
                        if (curl_global_init(CURL_GLOBAL_ALL)) {
                                throw NetworkException("Failed initialize cURL");
                        }
                }

                if ((curl = curl_easy_init()) == 0) {
                        throw NetworkException("Failed initialize cURL");
                }
        }

        CurlHandle::CurlHandle(const std::string & url)
            : CurlHandle()
        {
                if (CURLcode res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); res != 0) {
                        throw NetworkException("Failed set CURLOPT_URL", curl_easy_strerror(res));
                }
        }

        CurlHandle::~CurlHandle()
        {
                if (curl) {
                        curl_easy_cleanup(curl);
                }
                if (--init == 0) {
                        curl_global_cleanup();
                }
        }

        void CurlHandle::SetOption(CURLoption option, long value) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, value); res != 0) {
                        throw NetworkException("Failed set option", curl_easy_strerror(res));
                }
        }

        void CurlHandle::SetOption(CURLoption option, const char * value) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, value); res != 0) {
                        throw NetworkException("Failed set option", curl_easy_strerror(res));
                }
        }

        void CurlHandle::SetOption(CURLoption option, const std::string & value) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, value.c_str()); res != 0) {
                        throw NetworkException("Failed set option", curl_easy_strerror(res));
                }
        }

        void CurlHandle::SetOption(CURLoption option, Callback callback) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, callback); res != 0) {
                        throw NetworkException("Failed set callback", curl_easy_strerror(res));
                }
        }

        void CurlHandle::SetOption(CURLoption option, void * object) const
        {
                if (CURLcode res = curl_easy_setopt(curl, option, object); res != 0) {
                        throw NetworkException("Failed set object", curl_easy_strerror(res));
                }
        }

        void CurlHandle::Perform() const
        {
                if (CURLcode res = curl_easy_perform(curl); res != 0) {
                        throw NetworkException("Failed perform action", curl_easy_strerror(res));
                }
        }

        CurlStringList::CurlStringList()
            : list(nullptr)
        {
        }

        CurlStringList::CurlStringList(const char * value)
            : list(nullptr)
        {
                if (!(list = curl_slist_append(list, value))) {
                        throw NetworkException("Failed append list value", value);
                }
        }

        CurlStringList::CurlStringList(const std::string & value)
            : list(nullptr)
        {
                if (!(list = curl_slist_append(list, value.c_str()))) {
                        throw NetworkException("Failed append list value", value.c_str());
                }
        }

        CurlStringList::CurlStringList(const std::vector<const char *> & values)
            : list(nullptr)
        {
                for (auto value : values) {
                        if (!(list = curl_slist_append(list, value))) {
                                throw NetworkException("Failed append list value", value);
                        }
                }
        }

        CurlStringList::~CurlStringList()
        {
                curl_slist_free_all(list);
        }

        void CurlStringList::Append(const char * value)
        {
                if (!(list = curl_slist_append(list, value))) {
                        throw NetworkException("Failed append list value", value);
                }
        }

        void CurlStringList::Append(const std::string & value)
        {
                if (!(list = curl_slist_append(list, value.c_str()))) {
                        throw NetworkException("Failed append list value", value.c_str());
                }
        }

} // namespace Citrus::Logging

#endif // HAVE_LIBCURL
