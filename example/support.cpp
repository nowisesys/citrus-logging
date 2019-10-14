// Copyright (C) 2019 Anders Lövgren (Nowise Systems)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "support.hpp"
#include <iostream>
#include <vector>

using namespace Citrus::Logging;

void PrintFormat(const Format & format)
{
        std::cout << format.GetMessage(Record(Level::Debug, "Message 1"))
                  << format.GetMessage(Record(Level::Information, "Message 2"))
                  << format.GetMessage(Record(Level::Notice, "Message 3"))
                  << format.GetMessage(Record(Level::Warning, "Message 4"))
                  << format.GetMessage(Record(Level::Error, "Message 5"))
                  << format.GetMessage(Record(Level::Alert, "Message 6"))
                  << format.GetMessage(Record(Level::Critical, "Message 7"))
                  << format.GetMessage(Record(Level::Emergent, "Message 8"));
}

void PrintTarget(const Target & target)
{
        target.Append(Record(Level::Debug, "Message 1"));
        target.Append(Record(Level::Information, "Message 2"));
        target.Append(Record(Level::Notice, "Message 3"));
        target.Append(Record(Level::Warning, "Message 4"));
        target.Append(Record(Level::Error, "Message 5"));
        target.Append(Record(Level::Alert, "Message 6"));
        target.Append(Record(Level::Critical, "Message 7"));
        target.Append(Record(Level::Emergent, "Message 8"));
}

void PrintVector(const Target & target)
{
        std::vector<Record> records;

        records.push_back(Record(Level::Debug, "Message 1"));
        records.push_back(Record(Level::Information, "Message 2"));
        records.push_back(Record(Level::Notice, "Message 3"));
        records.push_back(Record(Level::Warning, "Message 4"));
        records.push_back(Record(Level::Error, "Message 5"));
        records.push_back(Record(Level::Alert, "Message 6"));
        records.push_back(Record(Level::Critical, "Message 7"));
        records.push_back(Record(Level::Emergent, "Message 8"));

        target.Append(records);
}

void PrintBuffer(const char * name, const std::vector<Record> & buffer)
{
        std::cout << name << "\n";
        for (const auto & record : buffer) {
                std::cout << record.GetDateTime().GetString() << ": " << record.GetMessage() << " (" << record.GetSeverity() << ")\n";
        }
}

void PrintStrategy(const char * name, MemoryStrategy * strategy)
{
        std::cout << name << "\n";
        for (int i = 0; i < 30; ++i) {
                strategy->Append(Record(std::to_string(i)));
        }
}
