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

using namespace Citrus::Logging;

void PrintFormat(const Format & format)
{
        std::cout << format.GetMessage(Record(Level::Debug, "Hello world"))
                  << format.GetMessage(Record(Level::Information, "Hello world"))
                  << format.GetMessage(Record(Level::Notice, "Hello world"))
                  << format.GetMessage(Record(Level::Warning, "Hello world"))
                  << format.GetMessage(Record(Level::Error, "Hello world"))
                  << format.GetMessage(Record(Level::Alert, "Hello world"))
                  << format.GetMessage(Record(Level::Critical, "Hello world"))
                  << format.GetMessage(Record(Level::Emergent, "Hello world"));
}

void PrintTarget(const Target & target)
{
        target.Append(Record(Level::Debug, "Hello world!"));
        target.Append(Record(Level::Information, "Hello world!"));
        target.Append(Record(Level::Notice, "Hello world!"));
        target.Append(Record(Level::Warning, "Hello world!"));
        target.Append(Record(Level::Error, "Hello world!"));
        target.Append(Record(Level::Alert, "Hello world!"));
        target.Append(Record(Level::Critical, "Hello world!"));
        target.Append(Record(Level::Emergent, "Hello world!"));
}

void PrintBuffer(const char * name, const std::vector<Record> & buffer)
{
        std::cout << name << "\n";
        for (auto & record : buffer) {
                std::cout << record.GetDateTime().GetString() << ": " << record.GetMessage() << "\n";
        }
}

void PrintStrategy(const char * name, MemoryStrategy * strategy)
{
        std::cout << name << "\n";
        for (int i = 0; i < 30; ++i) {
                strategy->Append(Record(std::to_string(i)));
        }
}
