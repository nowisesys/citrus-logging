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

#ifndef LIBCITRUS_UTILS_UUID_HPP
#define LIBCITRUS_UTILS_UUID_HPP

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBUUID

#include <string>
#include <vector>

#include <uuid.h>

namespace Citrus::Logging {

        class UuidGenerator
        {
            public:
                const int BufferSize = 36;

                enum struct Type
                {
                        Automatic,
                        Random,
                        Time,
                        timeSafe
                };

                UuidGenerator();
                UuidGenerator(Type type);

                operator std::string() const;

                Type GetType() const;
                std::vector<unsigned char> GetVector() const;
                std::string GetString() const;

                void Update();

                static std::string Next();
                static std::string Next(Type type);

            private:
                uuid_t uuid;
                Type type;
        };

} // namespace Citrus::Logging

#endif // HAVE_LIBUUID
#endif // LIBCITRUS_UTILS_UUID_HPP
