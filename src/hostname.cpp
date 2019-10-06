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

#include <cstring>
#include <string>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif

namespace Citrus::Logging {

        Hostname::Hostname()
        {
                hostname.resize(HOST_NAME_MAX);

                if (gethostname(hostname.data(), hostname.size()) < 0) {
                        throw NetworkException("Failed call gethostname", strerror(errno));
                }

                addrinfo hints = {0};
                addrinfo * res = 0;
                hints.ai_family = AF_UNSPEC;
                hints.ai_flags = AI_CANONNAME;

                if (getaddrinfo(hostname.c_str(), 0, &hints, &res) == 0) {
                        hostname = res->ai_canonname;
                        freeaddrinfo(res);
                }
        }

        const std::string Hostname::GetQualified() const
        {
                return hostname;
        }

        std::string Hostname::GetDomain() const
        {
                return hostname.substr(hostname.find_first_of('.') + 1);
        }

        std::string Hostname::GetShort() const
        {
                return hostname.substr(0, hostname.find_first_of('.'));
        }

        const Hostname & Hostname::GetInstance()
        {
                static Hostname shared;
                return shared;
        }

} // namespace Citrus::Logging
