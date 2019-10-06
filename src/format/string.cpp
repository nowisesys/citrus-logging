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

        FormatString::FormatString(const std::string & format)
            : format(format)
        {
        }

        std::string FormatString::GetMessage(const Record & record) const
        {
                Arguments arguments;

                arguments.push_back(record.GetDateTime().GetString());
                arguments.push_back(record.GetHostname().GetQualified());
                arguments.push_back(record.GetIdentity());
                arguments.push_back(record.GetMessage());
                arguments.push_back(record.GetPriority());
                arguments.push_back(record.GetProcess());

                return Message::Format(format.c_str(), arguments);
        }

} // namespace Citrus::Logging
