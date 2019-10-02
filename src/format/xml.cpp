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
                               const Format * format,
                               bool attrib,
                               const char * indent = "\t",
                               const char * newline = "\n")
        {
                std::ostringstream oss;

                oss << "<record>" << newline

                    << indent << "<datetime timezone=\""
                    << record.GetDateTime().GetTimeZone()
                    << "\" format=\"" << record.GetDateTime().GetFormat() << "\">"
                    << record.GetDateTime().GetString() << "</datetime>" << newline

                    << indent << "<priority>"
                    << record.GetPriority(format)
                    << "</priority>" << newline

                    << indent << "<identity>"
                    << record.GetIdentity()
                    << "</identity>" << newline

                    << indent << "<process>"
                    << record.GetProcess()
                    << "</process>" << newline

                    << indent << "<message>"
                    << record.GetMessage()
                    << "</message>" << newline

                    << "</record>\n";

                return oss.str();
        }

        std::string GetMessage(const Record & record,
                               const Format * format,
                               const char * indent = "\t",
                               const char * newline = "\n")
        {
                std::ostringstream oss;

                oss << "<record>" << newline

                    << indent << "<datetime>" << newline
                    << indent << indent << "<timezone>"
                    << record.GetDateTime().GetTimeZone()
                    << "</timezone>" << newline
                    << indent << indent << "<format>"
                    << record.GetDateTime().GetFormat()
                    << "</format>" << newline
                    << indent << indent << "<stamp>"
                    << record.GetDateTime().GetString()
                    << "</stamp>" << newline
                    << indent << "</datetime>" << newline

                    << indent << "<priority>"
                    << record.GetPriority(format)
                    << "</priority>" << newline

                    << indent << "<identity>"
                    << record.GetIdentity()
                    << "</identity>" << newline

                    << indent << "<process>"
                    << record.GetProcess()
                    << "</process>" << newline

                    << indent << "<message>"
                    << record.GetMessage()
                    << "</message>" << newline

                    << "</record>\n";

                return oss.str();
        }

} // namespace

namespace Citrus::Logging {

        FormatXml::FormatXml(bool pretty, bool attrib)
            : pretty(pretty), attrib(attrib) {}

        std::string FormatXml::GetMessage(const Record & record) const
        {
                if (pretty && attrib) {
                        return ::GetMessage(record, this, true);
                } else if (attrib) {
                        return ::GetMessage(record, this, true, "", "");
                } else if (pretty) {
                        return ::GetMessage(record, this);
                } else {
                        return ::GetMessage(record, this, "", "");
                }
        }

} // namespace Citrus::Logging
