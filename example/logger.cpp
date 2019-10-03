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

using namespace Citrus::Logging;

int main()
{
        Logger logger;
        int counter = 0;

        logger.Debug("Hello world!");
        logger.Debug("Hello world from %1 on year %2", {"logger", 2019});

        logger.Alert("Alert message (%d)", {++counter});
        logger.Critical("Critical message (%d)", {++counter});
        logger.Debug("Debug message (%d)", {++counter});
        logger.Emergent("Emergent message (%d)", {++counter});
        logger.Error("Error message (%d)", {++counter});
        logger.Information("Information message (%d)", {++counter});
        logger.Notice("Alert message (%d)", {++counter});

        logger(Level::Notice, "Notice message (?) logged by operator");
        logger(Level::Notice, "Notice message (%d) logged by operator", {++counter});

        return 0;
}
