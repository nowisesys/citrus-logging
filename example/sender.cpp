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

#include "logging.hpp"
#include <iostream>

using namespace Citrus::Logging;

int main()
{
        Sender sender;

        TargetFile target1("/tmp/output1.txt");
        TargetFile target2("/tmp/output2.txt");
        
        TargetStream target3(std::cout, RecordFormat<FormatJson>::Object());
        TargetStream target4(std::cout, RecordFormat<FormatText>::Object());
        TargetStream target5(std::cerr);

        sender.Register(&target1, Level::Debug, Level::Warning);
        sender.Register(&target2, Level::Error, Level::Emergent);
        sender.Register(&target3, Level::Debug, Level::Warning);
        sender.Register(&target4, Level::Debug, Level::Warning);
        sender.Register(&target5, Level::Error, Level::Emergent);

        sender.Write(Record());
        sender.Write(Level::Debug, "citrus-logger", "Hello World!");
        sender.Write(Level::Error, "citrus-logger", "Hello World!");
        sender.Write(Level::Error, "Hello World!");

        return 0;
}
