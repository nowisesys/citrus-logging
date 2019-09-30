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

namespace Citrus::Logging {

        void Sender::Register(Target * target)
        {
                for (int i = int(Level::Debug); i <= int(Level::Emergent); ++i) {
                        targets[Level(i)].push_back(target);
                }
        }

        void Sender::Register(Target * target, Level level)
        {
                targets[level].push_back(target);
        }

        void Sender::Register(Target * target, Level lower, Level upper)
        {
                for (int i = int(lower); i <= int(upper); ++i) {
                        targets[Level(i)].push_back(target);
                }
        }

        void Sender::Write(Level priority, const std::string & ident, const std::string & message) const
        {
                Write(Record(priority, ident, message));
        }

        void Sender::Write(const Record & record) const
        {
                Level priority = record.GetPriority();
                if (auto result = targets.find(priority); result != targets.end()) {
                        for (auto target : result->second) {
                                target->Append(record);
                        }
                }
        }

} // namespace Citrus::Logging
