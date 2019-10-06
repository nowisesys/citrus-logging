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

        void SetDefaultMapping(std::map<Level, std::string> & map)
        {
                map = {
                    {Level::Debug, Format::GetSeverity(Level::Debug)},
                    {Level::Information, Format::GetSeverity(Level::Information)},
                    {Level::Notice, Format::GetSeverity(Level::Notice)},
                    {Level::Warning, Format::GetSeverity(Level::Warning)},
                    {Level::Error, Format::GetSeverity(Level::Error)},
                    {Level::Alert, Format::GetSeverity(Level::Alert)},
                    {Level::Critical, Format::GetSeverity(Level::Critical)},
                    {Level::Emergent, Format::GetSeverity(Level::Emergent)},
                };
        }

        void SetLowerCaseMapping(std::map<Level, std::string> & map)
        {
                SetDefaultMapping(map);

                for (auto & entry : map) {
                        for (auto & c : entry.second) {
                                c = tolower(c);
                        }
                }
        }

        void SetUpperCaseMapping(std::map<Level, std::string> & map)
        {
                SetDefaultMapping(map);

                for (auto & entry : map) {
                        for (auto & c : entry.second) {
                                c = toupper(c);
                        }
                }
        }

        void SetShortTagMapping(std::map<Level, std::string> & map)
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
                        SetDefaultMapping(mapping);
                        break;
                case Mapping::LowerCase:
                        SetLowerCaseMapping(mapping);
                        break;
                case Mapping::UpperCase:
                        SetUpperCaseMapping(mapping);
                        break;

                case Mapping::ShortTag:
                        SetShortTagMapping(mapping);
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
