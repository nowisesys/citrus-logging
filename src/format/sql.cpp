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

        FormatSql::FormatSql()
            : table("logging")
        {
                columns = {
                    {"datetime", "datetime"},
                    {"priority", "priority"},
                    {"identity", "identity"},
                    {"process", "process"},
                    {"message", "message"},
                };
        }

        FormatSql::FormatSql(const std::string & table)
            : table(table)
        {
                columns = {
                    {"datetime", "datetime"},
                    {"priority", "priority"},
                    {"identity", "identity"},
                    {"process", "process"},
                    {"message", "message"},
                };
        }

        FormatSql::FormatSql(const std::string & table, const std::map<std::string, std::string> & columns)
            : table(table), columns(columns)
        {
        }

        std::string FormatSql::GetMessage(const Record & record) const
        {
                std::ostringstream oss;

                char enclose('"');
                char escape('\\');

                oss << "INSERT INTO " << table << "("
                    << columns.find("datetime")->second << ","
                    << columns.find("priority")->second << ","
                    << columns.find("identity")->second << ","
                    << columns.find("process")->second << ","
                    << columns.find("message")->second << ") "
                    << "VALUES("
                    << GetEscaped(record.GetDateTime().GetString(), enclose, escape) << ','
                    << GetEscaped(record.GetPriority(this), enclose, escape) << ','
                    << GetEscaped(record.GetIdentity(), enclose, escape) << ','
                    << GetEscaped(record.GetProcess(), enclose, escape) << ','
                    << GetEscaped(record.GetMessage(), enclose, escape)
                    << ");\n";

                return oss.str();
        }

} // namespace Citrus::Logging
