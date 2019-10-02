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
#include <algorithm>

namespace {
        using Level = Citrus::Logging::Level;
        using Format = Citrus::Logging::Format;

        void SetDefaultMapping(const Format * format, std::map<Level, std::string> & map)
        {
                map = {
                    {Level::Debug, format->GetPriority(Level::Debug)},
                    {Level::Information, format->GetPriority(Level::Information)},
                    {Level::Notice, format->GetPriority(Level::Notice)},
                    {Level::Warning, format->GetPriority(Level::Warning)},
                    {Level::Error, format->GetPriority(Level::Error)},
                    {Level::Alert, format->GetPriority(Level::Alert)},
                    {Level::Critical, format->GetPriority(Level::Critical)},
                    {Level::Emergent, format->GetPriority(Level::Emergent)},
                };
        }

        void SetLowerCaseMapping(const Format * format, std::map<Level, std::string> & map)
        {
                SetDefaultMapping(format, map);

                for (auto & entry : map) {
                        for (auto & c : entry.second) {
                                c = tolower(c);
                        }
                }
        }

        void SetUpperCaseMapping(const Format * format, std::map<Level, std::string> & map)
        {
                SetDefaultMapping(format, map);

                for (auto & entry : map) {
                        for (auto & c : entry.second) {
                                c = toupper(c);
                        }
                }
        }

        void SetShortTagMapping(const Format * format, std::map<Level, std::string> & map)
        {
                map = {
                    {Level::Debug, "[d]"},
                    {Level::Information, "[i]"},
                    {Level::Notice, "[!]"},
                    {Level::Warning, "[w]"},
                    {Level::Error, "[e]"},
                    {Level::Alert, "[*]"},
                    {Level::Critical, "[*]"},
                    {Level::Emergent, "[~]"},
                };
        }
} // namespace

namespace Citrus::Logging {

        FormatPrefix::FormatPrefix()
            : FormatPrefix(Mapping::Default)
        {
        }

        FormatPrefix::FormatPrefix(Mapping select)
        {
                switch (select) {
                case Mapping::Default:
                        SetDefaultMapping(this, mapping);
                        break;
                case Mapping::LowerCase:
                        SetLowerCaseMapping(this, mapping);
                        break;
                case Mapping::UpperCase:
                        SetUpperCaseMapping(this, mapping);
                        break;

                case Mapping::ShortTag:
                        SetShortTagMapping(this, mapping);
                        break;
                }
        }

        FormatPrefix::FormatPrefix(const std::map<Level, std::string> & mapping)
            : mapping(mapping)
        {
        }

        std::string FormatPrefix::GetMessage(const Record & record) const
        {
                return mapping.find(record.GetPriority())->second + ": " + record.GetMessage() + "\n";
        }

} // namespace Citrus::Logging
