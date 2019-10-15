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
#include <sstream>

namespace Citrus::Logging {

        struct LIBCITRUS_API_HIDDEN PlaceHolder
        {
                enum class Type
                {
                        Character,
                        Double,
                        Conversion,
                        Indexed
                };

                PlaceHolder(const char * format)
                    : curr(*(format + 0)),
                      next(*(format + 1))
                {
                        SetType();
                }

                void SetType()
                {
                        if (curr != '%') {
                                type = Type::Character;
                        } else if (next == '%') {
                                type = Type::Double;
                        } else if (isdigit(next)) {
                                type = Type::Indexed;
                        } else {
                                type = Type::Conversion;
                        }
                }

                int GetArgument() const
                {
                        return next - 1 - '0';
                }

                bool UseArgument() const
                {
                        return type == Type::Conversion ||
                               type == Type::Indexed;
                }

                char curr;
                char next;
                Type type;
        };

        std::string Message::Format(const char * format, const Arguments & args)
        {
                std::ostringstream iss;

                //
                // See sprintf(3) for conversion specifiers.
                //

                for (int argn = 0, index; *format != '\0'; ++format) {
                        PlaceHolder holder(format);

                        switch (holder.type) {
                        case PlaceHolder::Type::Character:
                                iss << holder.curr;
                                break;
                        case PlaceHolder::Type::Double:
                                iss << holder.curr;
                                break;
                        case PlaceHolder::Type::Conversion:
                                index = argn++;
                                break;
                        case PlaceHolder::Type::Indexed:
                                index = holder.GetArgument();
                        }

                        if (holder.UseArgument()) {
                                if (args[index].type() == typeid(int)) {
                                        iss << std::any_cast<int>(args[index]);
                                } else if (args[index].type() == typeid(double)) {
                                        iss << std::any_cast<double>(args[index]);
                                } else if (args[index].type() == typeid(float)) {
                                        iss << std::any_cast<float>(args[index]);
                                } else if (args[index].type() == typeid(char)) {
                                        iss << std::any_cast<char>(args[index]);
                                } else if (args[index].type() == typeid(bool)) {
                                        iss << std::boolalpha << std::any_cast<bool>(args[index]);
                                } else if (args[index].type() == typeid(const char *)) {
                                        iss << std::any_cast<const char *>(args[index]);
                                } else if (args[index].type() == typeid(std::string)) {
                                        iss << std::any_cast<std::string>(args[index]);
                                } else if (args[index].type() == typeid(Level)) {
                                        iss << Format::GetSeverity(std::any_cast<Level>(args[index]));
                                } else {
                                        throw InvalidArgumentException("Unknown conversion for specifier", holder.next);
                                }
                        }
                        if (holder.type != PlaceHolder::Type::Character) {
                                ++format;
                        }
                }

                return iss.str();
        }

        std::string Message::Format(const std::string & format, const Arguments & args)
        {
                return Format(format.c_str());
        }

} // namespace Citrus::Logging
