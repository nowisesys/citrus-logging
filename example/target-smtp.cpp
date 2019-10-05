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
#include <iostream>

using MailAddress = Citrus::Logging::TargetSmtp::Address;
using MailMessage = Citrus::Logging::TargetSmtp::Message;

static void PrintMessage(const MailMessage & message)
{
        std::cout << message.GetFormatted() << "\n";
}

static void TestFormat()
{
        MailMessage message;

        message.SetSubject("Test message");
        message.SetSender(MailAddress("anders@example.com", "Anders Lövgren"));
        message.AddRecipient(MailAddress("anders@example.com", "Anders Lövgren"));
        PrintMessage(message);

        message.AddHeader("X-Sender", "Citrus Logging Mailer");
        message.SetBodyText("Hello world!");
        PrintMessage(message);

        message.AddRecipient(MailAddress("olle@example.com", "Olle Svensson"));
        PrintMessage(message);

        message.AddRecipient(MailAddress("birgit@example.com", "Birgit skoghall"));
        message.AddRecipient(MailAddress("gunnar@example.com", "Gunnar Almqvist"));
        PrintMessage(message);
}

static void TestTarget()
{
        MailMessage message;

        message.SetSender("root@localhost", "Administrator");
        message.AddRecipient("andlov@home.qnet", "Anders Lövgren");
        message.SetSubject("SMTP target test");

        TargetSmtp target("smtp://smtp.unix.qnet", message);
        target.SetOption(CURLOPT_VERBOSE, 1);

        PrintTarget(target);
}

static void TestPrefix()
{
        //
        // Use prefix message formatting in upper case.
        //

        using Citrus::Logging::FormatPrefix;
        using Mapping = FormatPrefix::Mapping;

        MailMessage message;

        message.SetSender("root@localhost", "Administrator");
        message.AddRecipient("andlov@home.qnet", "Anders Lövgren");
        message.SetSubject("SMTP target test");

        TargetSmtp target("smtp://smtp.unix.qnet", message, RecordFormat<FormatPrefix, Mapping>::Object(Mapping::UpperCase));
        target.SetOption(CURLOPT_VERBOSE, 1);

        PrintTarget(target);
}

int main()
{
        TestFormat();
        TestTarget();
        TestPrefix();

        return 0;
}
