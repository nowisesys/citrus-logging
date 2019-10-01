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

#include "logging.hpp"
#include <iostream>

int main()
{
        using FormatSql = Citrus::Logging::FormatSql;
        using Record = Citrus::Logging::Record;

        FormatSql format1;
        std::cout << format1.GetMessage(Record("Hello world"))
                  << format1.GetMessage(Record("Hello world"));

        FormatSql format2("mytable");
        std::cout << format2.GetMessage(Record("Hello world"))
                  << format2.GetMessage(Record("Hello world"));

        FormatSql format3("mytable", {
                                         {"datetime", "stamp"},
                                         {"priority", "severity"},
                                         {"identity", "logger"},
                                         {"process", "pid"},
                                         {"message", "info"},
                                     });
        std::cout << format3.GetMessage(Record("Hello world"))
                  << format3.GetMessage(Record("Hello world"));

        return 0;
}
