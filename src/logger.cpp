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
#include <sstream>

namespace Citrus::Logging {

        Sender & Logger::GetSender()
        {
                return sender;
        }

        const Sender & Logger::GetSender() const
        {
                return sender;
        }

        void Logger::SetIdentity(const std::string & ident)
        {
                this->ident = ident;
        }

        void Logger::SetThreshold(Level level)
        {
                this->threshold = level;
        }

        void Logger::Message(Level level, const char * format, const Arguments & args) const
        {
                if (IsFiltered(level)) {
                        return;
                }

                Record record(level, ident, Message::Format(format, args));
                sender.Write(record);
        }

        void Logger::Emergent(const char * format, const Arguments & args) const
        {
                Message(Level::Emergent, format, args);
        }

        void Logger::Alert(const char * format, const Arguments & args) const
        {
                Message(Level::Alert, format, args);
        }

        void Logger::Critical(const char * format, const Arguments & args) const
        {
                Message(Level::Critical, format, args);
        }

        void Logger::Error(const char * format, const Arguments & args) const
        {
                Message(Level::Error, format, args);
        }

        void Logger::Warning(const char * format, const Arguments & args) const
        {
                Message(Level::Warning, format, args);
        }

        void Logger::Notice(const char * format, const Arguments & args) const
        {
                Message(Level::Notice, format, args);
        }

        void Logger::Information(const char * format, const Arguments & args) const
        {
                Message(Level::Debug, format, args);
        }

        void Logger::Debug(const char * format, const Arguments & args) const
        {
                Message(Level::Debug, format, args);
        }

        void Logger::operator()(Level level, const char * format) const
        {
                Message(level, format);
        }

        void Logger::operator()(Level level, const char * format, const Arguments & args) const
        {
                Message(level, format, args);
        }

        bool Logger::IsFiltered(Level level) const
        {
                return static_cast<int>(level) < static_cast<int>(threshold);
        }

} // namespace Citrus::Logging
