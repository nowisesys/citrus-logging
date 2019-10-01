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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logging.hpp"
#include <iostream>

int main()
{
        using Message = Citrus::Logging::Message;

        std::cout << Message::Format("Use conversion %s (char='%c', float='%f', bool='%b')'", {"hello", 'C', 64.340043625, true}) << "\n";
        std::cout << Message::Format("Use indexes %1 %2 %1", {"arg1", 4949}) << "\n";

        return 0;
}
