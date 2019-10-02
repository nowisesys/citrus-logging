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
        PrintTarget(TargetHttp("http://localhost/http.php"));
        PrintTarget(TargetHttp("http://localhost/http.php", FormatXml()));

        TargetHttp target("http://localhost/http.php");
        target.AddHeader("Content-Type: application/json");
        target.AddHeader("X-Sender", "Citrus Logging");
        target.SetOption(CURLOPT_VERBOSE, 1);
        PrintTarget(target);

        return 0;
}
