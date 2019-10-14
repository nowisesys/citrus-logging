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

class Synchronize
{
    public:
        void operator()(const MemoryStrategy * strategy)
        {
                PrintBuffer("Operator:", strategy->GetBuffer());
        }
};

int main()
{
        //
        // Silent: uses the default overflow handler.
        //
        PrintTarget(TargetMemory(2));

        //
        // Calls lambda function for every second record.
        //
        PrintTarget(TargetMemory([](const MemoryStrategy * strategy) {
                PrintBuffer("Lambda (1):", strategy->GetBuffer());
        },
                                 2));

        //
        // Same as previous, but testing memory strategy pointer.
        //
        TargetMemory target(2);
        target.GetMemoryStrategy()
            ->OnOverflow([](const MemoryStrategy * strategy) {
                    PrintBuffer("Lambda (2):", strategy->GetBuffer());
            });
        PrintTarget(target);

        //
        // Pass memory strategy for constructor.
        //
        PrintTarget(TargetMemory(new MemoryStrategyLinear(2)));

        //
        // Uses functional object.
        //
        PrintTarget(TargetMemory(Synchronize(), 2));

        return 0;
}
