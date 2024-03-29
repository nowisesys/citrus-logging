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

#include "support.hpp"
#include <iostream>

int main()
{
        PrintTarget(TargetStream(std::cout));
        PrintTarget(TargetStream(std::cerr));

        PrintTarget(TargetStream(std::cout, FormatText()));
        PrintTarget(TargetStream(std::cout, FormatCsv()));
        PrintTarget(TargetStream(std::cout, FormatJson()));
        PrintTarget(TargetStream(std::cout, FormatSql()));

        return 0;
}
