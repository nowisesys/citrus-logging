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

//
// This example demonstate how to define multiple log targets and
// connecting them with severity levels. An implementation would derive
// from the logger class.
//

#include "logging.hpp"
#include <iostream>

using namespace Citrus::Logging;

int main()
{
        Logger logger;
        int counter = 0;

        //
        // Create log targets:
        //
        TargetFile target1("/tmp/citrus-debug.txt");
        TargetFile target2("/tmp/citrus-system.txt", RecordFormat<FormatJson>::Object());

        TargetStream target3(std::cerr, RecordFormat<FormatPrefix>::Object());
        TargetStream target4(std::cout, RecordFormat<FormatXml>::Object());

        //
        // Connect severity levels with log targets:
        //
        logger.GetSender().Register(&target1, Level::Debug);
        logger.GetSender().Register(&target2, Level::Information, Level::Emergent);
        logger.GetSender().Register(&target3, Level::Error, Level::Emergent);
        logger.GetSender().Register(&target4, Level::Notice, Level::Warning);

        //
        // Set severity threshold (will display all messages):
        //
        logger.SetThreshold(Level::Debug);

        //
        // Use method to severity mapping methods:
        //
        logger.Debug("Hello world!");
        logger.Debug("Hello world from %1 on year %2", {"logger", 2019});

        logger.Alert("Alert message (%d)", {++counter});
        logger.Critical("Critical message (%d)", {++counter});
        logger.Debug("Debug message (%d)", {++counter});
        logger.Emergent("Emergent message (%d)", {++counter});
        logger.Error("Error message (%d)", {++counter});
        logger.Information("Information message (%d)", {++counter});
        logger.Notice("Alert message (%d)", {++counter});

        //
        // Use alternative operator logging methods:
        //
        logger(Level::Notice, "Notice message (?) logged by operator");
        logger(Level::Notice, "Notice message (%d) logged by operator", {++counter});

        return 0;
}
