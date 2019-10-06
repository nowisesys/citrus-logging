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

#include "utils/escape.hpp"
#include "logging.hpp"
#include <iomanip>
#include <sstream>
#include <string>

namespace Citrus::Logging {

        FormatCsv::FormatCsv(char delimit, char enclose, char escape)
            : delimit(delimit), enclose(enclose), escape(escape) {}

        std::string FormatCsv::GetMessage(const Record & record) const
        {
                std::ostringstream oss;

                oss << GetEscaped(record.GetDateTime().GetString(), enclose, escape) << delimit
                    << GetEscaped(record.GetSeverity(), enclose, escape) << delimit
                    << GetEscaped(record.GetIdentity(), enclose, escape) << delimit
                    << GetEscaped(record.GetProcess(), enclose, escape) << delimit
                    << GetEscaped(record.GetMessage(), enclose, escape) << '\n';

                return oss.str();
        }

} // namespace Citrus::Logging
