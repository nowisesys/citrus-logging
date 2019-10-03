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
// This example demonstate how to connect mutiple log targets with
// severity levels for unified logging thru the logger.
//

#include "derived.hpp"

using namespace MyApp;

int main()
{
        //
        // Will log all messages with given identity:
        //
        Logger logger(Level::Debug, "myapp-derived");

        //
        // Simple log message without parameters:
        //
        logger.Debug("Hello world!");

        //
        // Use position substitution:
        //
        logger.Debug("Hello world from %1 on year %2", {"logger", 2019});

        //
        // Use conversion specifiers:
        //
        logger.Debug("Hello world from %s on year %d", {"logger", 2019});

        //
        // Use severity convenience methods:
        //
        logger.Debug("Some log message");
        logger.Information("Some log message");
        logger.Notice("Some log message");
        logger.Warning("Some log message");
        logger.Error("Some log message");
        logger.Critical("Some log message");
        logger.Alert("Some log message");
        logger.Emergent("Some log message");

        //
        // Use alternative operator logging methods:
        //
        logger(Level::Notice, "Notice message (1) logged by operator");
        logger(Level::Notice, "Notice message (%d) logged by operator", {2});

        return 0;
}
