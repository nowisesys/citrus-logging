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

        MemoryStrategyCircular::MemoryStrategyCircular(size_type size)
            : size(size), curr(0)
        {
                if (size <= 0) {
                        throw InvalidArgumentException("The size must be larger or equal to one", std::to_string(size));
                }

                buffer.resize(size);
        }

        MemoryStrategyCircular::MemoryStrategyCircular(Callback callback, size_type size)
            : MemoryStrategyCircular(size)
        {
                this->callback = callback;
        }

        void MemoryStrategyCircular::Append(const Record & record)
        {
                buffer[curr++] = record;

                if (curr == size) {
                        callback(this);
                        curr = 0;
                }
        }

        const std::vector<Record> & MemoryStrategyCircular::GetBuffer() const
        {
                if (curr == size) {
                        return buffer;
                }

                std::vector<Record> result;

                result.assign(buffer.begin() + curr, buffer.end());
                result.assign(buffer.begin(), buffer.begin() + curr);

                return std::move(result);
        }

} // namespace Citrus::Logging
