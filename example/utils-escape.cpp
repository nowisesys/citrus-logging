// Copyright (C) 2019 Anders Lövgren (Nowise Systems)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "utils/escape.hpp"
#include <iostream>

using namespace Citrus::Logging;

template <typename T>
static void PrintEscaped(const T & value)
{
        std::cout << "Value: '" << value << "', Escaped: '" << GetEscaped(value) << "'\n";
}

template <typename T>
static void PrintEscaped(const T & value, char enclose, char escape)
{
        std::cout << "Value: '" << value << "', Escaped: '" << GetEscaped(value, enclose, escape) << "'\n";
}

int main()
{
        PrintEscaped("test");
        PrintEscaped(std::string("test"));
        PrintEscaped(15);

        PrintEscaped("test with \"quoted\" word inside");
        PrintEscaped(std::string("test with \"quoted\" word inside"));

        PrintEscaped("test", '@', ' ');
        PrintEscaped("test", '|', ' ');

        return 0;
}
