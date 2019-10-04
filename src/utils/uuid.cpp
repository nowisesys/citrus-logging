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

#include "uuid.hpp"

#ifdef HAVE_LIBUUID

namespace Citrus::Logging {

        UuidGenerator::UuidGenerator()
            : type(Type::Automatic)
        {
                Update();
        }

        UuidGenerator::UuidGenerator(Type type)
            : type(type)
        {
                Update();
        }

        UuidGenerator::operator std::string() const
        {
                return GetString();
        }

        UuidGenerator::Type UuidGenerator::GetType() const
        {
                return type;
        }

        std::vector<unsigned char> UuidGenerator::GetVector() const
        {
                return std::vector<unsigned char>(uuid, uuid + 16);
        }

        std::string UuidGenerator::GetString() const
        {
                std::string result;

                result.resize(BufferSize);
                uuid_unparse_lower(uuid, result.data());

                return result;
        }

        void UuidGenerator::Update()
        {
                switch (type) {
                case Type::Automatic:
                        uuid_generate(uuid);
                        break;
                case Type::Random:
                        uuid_generate_random(uuid);
                        break;
                case Type::Time:
                        uuid_generate_time(uuid);
                        break;
                case Type::timeSafe:
                        uuid_generate_time_safe(uuid);
                        break;
                }
        }

        std::string UuidGenerator::Next()
        {
                return UuidGenerator();
        }

        std::string UuidGenerator::Next(Type type)
        {
                return UuidGenerator(type);
        }

} // namespace Citrus::Logging

#endif // HAVE_LIBUUID
