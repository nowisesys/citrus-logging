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
        MemoryStrategyLinear strategy1(6);
        strategy1.OnOverflow([](const MemoryStrategy * strategy) {
                PrintBuffer("+ Overflow (1)!", strategy->GetBuffer());
        });

        MemoryStrategyLinear strategy2([](const MemoryStrategy * strategy) {
                PrintBuffer("+ Overflow (2)!", strategy->GetBuffer());
        });

        PrintBuffer("+ Buffer (1):", strategy1.GetBuffer());
        PrintBuffer("+ Buffer (2):", strategy2.GetBuffer());

        PrintStrategy("+ Strategy (1)", &strategy1);
        PrintStrategy("+ Strategy (2)", &strategy2);

        PrintBuffer("+ Buffer (1):", strategy1.GetBuffer());
        PrintBuffer("+ Buffer (2):", strategy2.GetBuffer());

        return 0;
}
