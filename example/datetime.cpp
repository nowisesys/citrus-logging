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
#include <iomanip>
#include <iostream>

using DateTime = Citrus::Logging::DateTime;

static void PrintDateTime(const DateTime & datetime)
{
        std::cout << std::left << std::setw(35) << datetime.GetString()
                  << "[format='" << datetime.GetFormat() << "']\n";
}

int main()
{
        PrintDateTime(DateTime());
        PrintDateTime(DateTime(DateTime::TimeClock::now()));

        std::cout << "\nTimezone: " << DateTime().GetTimeZone() << "\n";

        PrintDateTime(DateTime(DateTime::Format::Database));
        PrintDateTime(DateTime(DateTime::Format::Epoch));
        PrintDateTime(DateTime(DateTime::Format::Human));
        PrintDateTime(DateTime(DateTime::Format::Locale));
        PrintDateTime(DateTime(DateTime::Format::Timezone));
        PrintDateTime(DateTime(DateTime::Format::ISO8601));

        DateTime().SetTimeZone("Asia/Tokyo");
        std::cout << "\nTimezone: " << DateTime().GetTimeZone() << "\n";

        PrintDateTime(DateTime(DateTime::Format::Database));
        PrintDateTime(DateTime(DateTime::Format::Epoch));
        PrintDateTime(DateTime(DateTime::Format::Human));
        PrintDateTime(DateTime(DateTime::Format::Locale));
        PrintDateTime(DateTime(DateTime::Format::Timezone));
        PrintDateTime(DateTime(DateTime::Format::ISO8601));

        DateTime().SetTimeZone("America/Vancouver");
        std::cout << "\nTimezone: " << DateTime().GetTimeZone() << "\n";

        PrintDateTime(DateTime(DateTime::Format::Database));
        PrintDateTime(DateTime(DateTime::Format::Epoch));
        PrintDateTime(DateTime(DateTime::Format::Human));
        PrintDateTime(DateTime(DateTime::Format::Locale));
        PrintDateTime(DateTime(DateTime::Format::Timezone));
        PrintDateTime(DateTime(DateTime::Format::ISO8601));

        return 0;
}
