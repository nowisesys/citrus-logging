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
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace Citrus::Logging {

        const char * DateTime::Format::Human = "%c";
        const char * DateTime::Format::Database = "%Y-%m-%d %H:%M:%S";
        const char * DateTime::Format::Epoch = "%s";
        const char * DateTime::Format::Locale = "%x %X";
        const char * DateTime::Format::Timezone = "%c %Z";
        const char * DateTime::Format::ISO8601 = "%FT%T%z"; // "%Y-%m-%dT%H:%M:%SZ";

        DateTime::DateTime()
            : format(Format::Human), stamp(TimeClock::now())
        {
        }

        DateTime::DateTime(const char * format)
            : format(format), stamp(TimeClock::now())
        {
        }

        DateTime::DateTime(const char * format, const TimePoint & stamp)
            : format(format), stamp(stamp)
        {
        }

        DateTime::DateTime(const TimePoint & stamp)
            : format(Format::Human), stamp(stamp)
        {
        }

        void DateTime::SetFormat(const char * format)
        {
                this->format = format;
        }

        const char * DateTime::GetFormat() const
        {
                return format;
        }

        void DateTime::SetTimePoint(const TimePoint & stamp)
        {
                this->stamp = stamp;
        }

        const DateTime::TimePoint & DateTime::GetTimePoint() const
        {
                return stamp;
        }

        void DateTime::SetTimeZone(const char * tz)
        {
                static std::string timezone; // Need static storage

                timezone = "TZ=" + std::string(tz);
                putenv(timezone.data());
        }

        const char * DateTime::GetTimeZone() const
        {
                return getenv("TZ") ? getenv("TZ") : "";
        }

        std::string DateTime::GetString() const
        {
                std::ostringstream oss;
                std::time_t timed = TimeClock::to_time_t(stamp);

                oss << std::put_time(std::localtime(&timed), format);
                return oss.str();
        }

        DateTime DateTime::Now(const char * format)
        {
                return DateTime(format);
        }

} // namespace Citrus::Logging
