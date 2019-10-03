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

#ifndef LIBCITRUS_EXAMPLE_DERIVED_HPP
#define LIBCITRUS_EXAMPLE_DERIVED_HPP

#include "logging.hpp"
#include <iostream>
#include <vector>

namespace MyApp {

        using Level = Citrus::Logging::Level;

        using Target = Citrus::Logging::Target;
        using Parent = Citrus::Logging::Logger;

        class Logger : public Parent
        {
            public:
                Logger(Level threshold = Level::Information, const std::string & ident = "")
                {
                        using namespace Citrus::Logging;

                        //
                        // Create log targets:
                        //
                        Target * target1 = new TargetFile("/tmp/citrus-debug.txt");
                        Target * target2 = new TargetFile("/tmp/citrus-system.txt", RecordFormat<FormatJson>::Object());

                        Target * target3 = new TargetStream(std::cerr, RecordFormat<FormatPrefix>::Object());
                        Target * target4 = new TargetStream(std::cout, RecordFormat<FormatXml>::Object());

                        //
                        // Connect severity levels with log targets:
                        //
                        GetSender().Register(target1, Level::Debug);
                        GetSender().Register(target2, Level::Information, Level::Emergent);
                        GetSender().Register(target3, Level::Error, Level::Emergent);
                        GetSender().Register(target4, Level::Notice, Level::Warning);

                        //
                        // Set severity threshold:
                        //
                        SetThreshold(threshold);

                        //
                        // The identity will be include in each log message:
                        //
                        SetIdentity(ident);

                        //
                        // Keep track of log targets:
                        //
                        targets.push_back(target1);
                        targets.push_back(target2);
                        targets.push_back(target3);
                        targets.push_back(target4);
                }

                ~Logger()
                {
                        for (auto & target : targets) {
                                delete target;
                        }
                }

            private:
                std::vector<Target *> targets;
        };
} // namespace MyApp

#endif // LIBCITRUS_EXAMPLE_DERIVED_HPP
