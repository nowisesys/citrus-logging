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

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

namespace Citrus::Logging {

        Record::Record()
            : priority(Level::Information)
        {
                SetProcess();
        }

        Record::Record(const std::string & message)
            : priority(Level::Information), message(message)
        {
                SetProcess();
        }

        Record::Record(Level priority, const std::string & ident, const std::string & message)
            : priority(priority), ident(ident), message(message)
        {
                SetProcess();
        }

        void Record::SetPriority(Level priority)
        {
                this->priority = priority;
        }

        void Record::SetIdentity(const std::string & ident)
        {
                this->ident = ident;
        }

        void Record::SetMessage(const std::string & message)
        {
                this->message = message;
        }

        std::string Record::GetPriority(const Format * format) const
        {
                return format->GetPriority(priority);
        }

        Level Record::GetPriority() const
        {
                return priority;
        }

        const std::string & Record::GetIdentity() const
        {
                return ident;
        }

        const std::string & Record::GetMessage() const
        {
                return message;
        }

        int Record::GetProcess() const
        {
                return pid;
        }

        const DateTime & Record::GetDateTime() const
        {
                return stamp;
        }

        void Record::SetProcess()
        {
                pid = getpid();
        }

} // namespace Citrus::Logging
