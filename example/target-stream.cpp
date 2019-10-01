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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logging.hpp"
#include <iostream>

using namespace Citrus::Logging;

static void PrintTarget(std::ostream & stream, const Format & format)
{
        TargetStream target(stream, format);
        target.Append(Record("Hello world!"));
        target.Append(Record("Hello world!"));
}

int main()
{
        PrintTarget(std::cout, FormatText());
        PrintTarget(std::cout, FormatCsv());
        PrintTarget(std::cout, FormatJson());
        PrintTarget(std::cout, FormatSql());

        return 0;
}
