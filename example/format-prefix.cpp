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

// using namespace Citrus::Logging;
using Mapping = FormatPrefix::Mapping;

int main()
{
        PrintFormat(FormatPrefix());

        PrintFormat(FormatPrefix(Mapping::Default));
        PrintFormat(FormatPrefix(Mapping::LowerCase));
        PrintFormat(FormatPrefix(Mapping::UpperCase));
        PrintFormat(FormatPrefix(Mapping::ShortTag));

        PrintFormat(FormatPrefix({
            {Level::Debug, "[+] <D>"},
            {Level::Information, "[+] <I>"},
            {Level::Notice, "[+] <N>"},
            {Level::Warning, "[-] <W>"},
            {Level::Error, "[-] <E>"},
            {Level::Alert, "[!] <A>"},
            {Level::Critical, "[!] <C>"},
            {Level::Emergent, "[!] <E>"},
        }));

        return 0;
}
