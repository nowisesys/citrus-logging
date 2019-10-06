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

namespace {

        using Record = Citrus::Logging::Record;
        using Format = Citrus::Logging::Format;

        std::string GetMessage(const Record & record,
                               const char * resep = "\n",
                               const char * sline = "\t",
                               const char * eline = "\n",
                               const char * quote = "\"")
        {
                std::ostringstream oss;

                oss << '{' << eline

                    << sline
                    << quote << "datetime" << quote << ':'
                    << quote << record.GetDateTime().GetString() << quote << ','
                    << eline

                    << sline
                    << quote << "hostname" << quote << ':'
                    << quote << record.GetHostname().GetQualified() << quote << ','
                    << eline

                    << sline
                    << quote << "priority" << quote << ':'
                    << quote << record.GetSeverity() << quote << ','
                    << eline

                    << sline
                    << quote << "identity" << quote << ':'
                    << quote << record.GetIdentity() << quote << ','
                    << eline

                    << sline
                    << quote << "process" << quote << ':'
                    << record.GetProcess() << ','
                    << eline

                    << sline
                    << quote << "message" << quote << ':'
                    << quote << record.GetMessage() << quote
                    << eline

                    << '}' << eline
                    << resep;

                return oss.str();
        }

} // namespace

namespace Citrus::Logging {

        FormatJson::FormatJson(bool pretty)
            : pretty(pretty) {}

        std::string FormatJson::GetMessage(const Record & record) const
        {
                if (pretty) {
                        return ::GetMessage(record, "");
                } else {
                        return ::GetMessage(record, "\n", "", "");
                }
        }

} // namespace Citrus::Logging
