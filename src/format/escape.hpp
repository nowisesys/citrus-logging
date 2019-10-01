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

#ifndef LIBCITRUS_FORMAT_ESCAPE_HPP
#define LIBCITRUS_FORMAT_ESCAPE_HPP

#include <iomanip>
#include <string>

extern std::string GetEscaped(std::string input, char enclose, char escape);

template <typename T>
std::string GetEscaped(T input, char enclose, char escape)
{
        return std::to_string(input);
}

#endif // LIBCITRUS_FORMAT_ESCAPE_HPP
