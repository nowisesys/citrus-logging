// Copyright (C) 2019 Anders Lövgren (Nowise Systems)
//
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "logging.hpp"

namespace Citrus::Logging {

        MemoryStrategyLinear::MemoryStrategyLinear(size_type size)
            : size(size)
        {
                if (size <= 0) {
                        throw InvalidArgumentException("The size must be larger or equal to one", std::to_string(size));
                }

                buffer.reserve(size);
        }

        MemoryStrategyLinear::MemoryStrategyLinear(Callback callback, size_type size)
            : MemoryStrategyLinear(size)
        {
                this->callback = callback;
        }

        MemoryStrategyLinear::~MemoryStrategyLinear()
        {
                if (buffer.size() != 0) {
                        callback(this); // Has unsynced records
                }
        }

        void MemoryStrategyLinear::Append(const Record & record)
        {
                buffer.push_back(record);

                if (buffer.size() == size) {
                        callback(this);
                        buffer.clear();
                }
        }

        std::vector<Record> MemoryStrategyLinear::GetBuffer() const
        {
                return buffer;
        }

        std::vector<Record> MemoryStrategyLinear::GetLatest() const
        {
                return buffer;
        }

} // namespace Citrus::Logging
