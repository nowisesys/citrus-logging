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

int main()
{
        MemoryStrategyLinear strategy1(3);
        strategy1.OnOverflow([](const MemoryStrategy * strategy) {
                PrintBuffer("+ Overflow (1L)!", strategy->GetLatest());
                PrintBuffer("+ Overflow (1B)!", strategy->GetBuffer());
        });

        MemoryStrategyLinear strategy2([](const MemoryStrategy * strategy) {
                PrintBuffer("+ Overflow (2L)!", strategy->GetLatest());
                PrintBuffer("+ Overflow (2B)!", strategy->GetBuffer());
        }); // Has size == 25 by default

        PrintBuffer("+ Buffer (1L):", strategy1.GetLatest());
        PrintBuffer("+ Buffer (2L):", strategy2.GetLatest());
        PrintBuffer("+ Buffer (1B):", strategy1.GetBuffer());
        PrintBuffer("+ Buffer (2B):", strategy2.GetBuffer());

        PrintStrategy("+ Strategy (1)", &strategy1);
        PrintStrategy("+ Strategy (2)", &strategy2);

        PrintBuffer("+ Buffer (1L):", strategy1.GetLatest());
        PrintBuffer("+ Buffer (2L):", strategy2.GetLatest());
        PrintBuffer("+ Buffer (1B):", strategy1.GetBuffer());
        PrintBuffer("+ Buffer (2B):", strategy2.GetBuffer());

        strategy1.Append(Record("test 1"));
        strategy1.Append(Record("test 2"));
        strategy1.Append(Record("test 3")); // <- Causes overflow
        strategy1.Append(Record("test 4"));

        PrintBuffer("+ Buffer (1L):", strategy1.GetLatest());
        PrintBuffer("+ Buffer (1B):", strategy1.GetBuffer());

        return 0;
}
