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

        FormatText::FormatText(char field, char lines)
            : field(field), lines(lines) {}

        std::string FormatText::GetMessage(const Record & record) const
        {
                std::ostringstream oss;

                oss << record.GetDateTime().GetString() << field
                    << record.GetPriority(this) << field
                    << record.GetIdentity() << field
                    << record.GetProcess() << field
                    << record.GetMessage() << lines;

                return oss.str();
        }

} // namespace Citrus::Logging
