# Citrus C++

## Multiplexed logger for C++ (citrus-logging)

Logging consists of targets and their associated formatter. An log target is connected with various severity levels in a many-to-many configuration as registered with the record message sender (obtained by reference from the logger during initialization).

For use in an application, the logger class is the central piece that provides convenient methods for logging. See the [inherit logger class](example/derived.hpp) example with its [test driver](example/derived.cpp) for an real-world example on using citrus-logging in an application.

## Example

In this example we are using file and stream targets. Any message with severity error or higher will be logged to both myapp-system.txt and stderr. It also demonstrate using ordinal substitution and conversion specifiers for log message formatting.

```c++
#include <iostream>
#include <citrus/logging.hpp>

using namespace Citrus::Logging;

int main(int argc, const char **argv)
{
        Logger logger;

        TargetFile target1("/var/log/myapp-debug.txt");
        TargetFile target2("/var/log/myapp-system.txt", RecordFormat<FormatJson>::Object());
        TargetStream target3(std::cerr, RecordFormat<FormatPrefix>::Object());

        logger.GetSender().Register(&target1, Level::Debug);
        logger.GetSender().Register(&target2, Level::Information, Level::Emergent);
        logger.GetSender().Register(&target3, Level::Error, Level::Emergent);

        logger.SetThreshold(Level::Debug);
        logger.SetIdentity("my-logger");

        logger.Debug("Hello world!");
        logger.Debug("Hello world from %1 on year %2", {"logger", 2019});

        std::string message("Logging is simple!");

        logger.Alert("Alert message (%s)", {message});
        logger.Critical("Critical message (%s)", {message});
        logger.Debug("Debug message (%s)", {message});
        logger.Emergent("Emergent message (%s)", {message});
        logger.Error("Error message (%s)", {message});
        logger.Information("Information message (%s)", {message});
        logger.Notice("Alert message (%s)", {message});

        logger(Level::Notice, "Notice message logged by operator");
        logger(Level::Notice, "Notice message logged by operator (%s)", {message});

        return 0;
}
```
Have a look inside the [example directory](example) for simple programs that demonstrate each class in the citrus-logging library.

## Targets

The list of targets consist of **File**, **HTTP**, **SMTP**, **I/O Stream**, **Memory** and **UNIX syslog**. Each target class has a default formatter that can be replaced by passing a second argument. In this example, the first **http** target will format messages as JSON, while the second will format as XML.

```c++
TargetHttp target1("http://localhost/http.php");
TargetHttp target2("http://localhost/http.php", RecordFormat<FormatXml>::Object());
```

### Custom methods

Some targets provides utility methods. For example, the **HTTP** and **SMTP** targets provides wrapper for passing options to libcurl:
```c++
TargetSmtp target("smtp://smtp.unix.qnet", message, formatter);
target.SetOption(CURLOPT_VERBOSE, 1);
```

## Formatters

The list of formatters consist of numerous classes, i.e. **JSON**, **SQL**, **CSV**, **XML** and most target classes uses sensible default formatters. 

### Customize
If these don't suite your taste, you can either create your own custom format classes or use the swiss-army knife classes **String** (format specifier) or **User** (lambda callback):

```c++
FormatString format1("[%3][%2][%6] %1 <%5>: %4\n")
FormatUser   format2([](const Record & record) -> std::string {
                return record.GetDateTime().GetString(DateTime::Format::ISO8601) + ": " + record.GetMessage() + "\n";
        });
```

## Requirements

A decent C++ compiler supporting version 11 should be sufficient. Some parts uses version 17 with code emulation for non-conforming compilers (i.e. lack of std::map<K,V>::merge()).

For building the HTTP and SMTP logger you need to have libcurl installed with development headers and relevant protocols enabled.

## Building

A standard installation into /usr/local:

```bash
bash$> ./autogen.sh
bash$> ./configure
bash$> make && make install
```

Pass --prefix=path to configure or use environment variable DESTDIR for installation to non-standard locations.

## Getting started

See the examples directory for complete code ready to be run.

## License

This library is released under LGPL-3.0 and can be linked and used with commercial applications.

## Bug report & suggestions

Please see the AUTHORS file for contact information. Feel free to submit bug reports and suggestions.
