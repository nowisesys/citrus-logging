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
#include <iostream>

int main()
{
        using FormatText = Citrus::Logging::FormatText;
        using FormatJson = Citrus::Logging::FormatJson;
        using FormatCvs = Citrus::Logging::FormatCvs;

        using TargetFile = Citrus::Logging::TargetFile;
        using Record = Citrus::Logging::Record;

        TargetFile target1("/tmp/output.txt", FormatText());
        target1.Append(Record("Hello world!"));
        target1.Append(Record("Hello world!"));

        TargetFile target2("/tmp/output.cvs", FormatCvs());
        target2.Append(Record("Hello world!"));
        target2.Append(Record("Hello world!"));

        TargetFile target3("/tmp/output.json", FormatJson());
        target3.Append(Record("Hello world!"));
        target3.Append(Record("Hello world!"));

        return 0;
}
