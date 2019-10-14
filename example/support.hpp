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

#ifndef LIBCITRUS_EXAMPLE_SUPPORT_HPP
#define LIBCITRUS_EXAMPLE_SUPPORT_HPP

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logging.hpp"

using namespace Citrus::Logging;

void PrintFormat(const Format & format);
void PrintTarget(const Target & target);
void PrintVector(const Target & target);

void PrintBuffer(const char * name, const std::vector<Record> & buffer);
void PrintStrategy(const char * name, MemoryStrategy * strategy);

#endif // LIBCITRUS_EXAMPLE_SUPPORT_HPP
