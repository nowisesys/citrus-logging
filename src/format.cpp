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
#include <map>

namespace Citrus::Logging {

        std::string Format::GetPriority(Level level) const
        {
                static std::map<Level, const char *> mapper = {
                    {Level::Emergent, "Emergent"},
                    {Level::Alert, "Alert"},
                    {Level::Critical, "Critical"},
                    {Level::Error, "Error"},
                    {Level::Warning, "Warning"},
                    {Level::Notice, "Notice"},
                    {Level::Information, "Information"},
                    {Level::Debug, "Debug"},
                };

                return mapper[level];
        }

} // namespace Citrus::Logging
