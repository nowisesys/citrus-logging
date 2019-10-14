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

        //
        // Test i.e. move assignments.
        //
        TargetMemory target1, target2;

        target1.Append(Record());
        PrintBuffer("Target 1A:", target1.GetMemoryStrategy()->GetBuffer()); // 1 record
        PrintBuffer("Target 2A:", target2.GetMemoryStrategy()->GetBuffer()); // 0 record

        target2 = target1;                                                   // Will duplicate records too
        PrintBuffer("Target 1B:", target1.GetMemoryStrategy()->GetBuffer()); // 1 record
        PrintBuffer("Target 2B:", target2.GetMemoryStrategy()->GetBuffer()); // 1 record

        target1 = target1;
        target2.Append(Record(Level::Notice, "Second target"));
        PrintBuffer("Target 1C:", target1.GetMemoryStrategy()->GetBuffer()); // 1 record
        PrintBuffer("Target 2C:", target2.GetMemoryStrategy()->GetBuffer()); // 2 record

        target1 = std::move(target2);
        PrintBuffer("Target 1D:", target1.GetMemoryStrategy()->GetBuffer()); // 2 record
        // PrintBuffer("Target 2D:", target2.GetMemoryStrategy()->GetBuffer()); // No longer valid

        return 0;
}
