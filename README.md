# Citrus C++

## Multiplexed logger for C++ (citrus-logging)

## Example

```c++
```

## Requirements

A decent C++ compiler supporting version 11 should be sufficient. Some parts uses version 17 with code emulation for non-conforming compilers (i.e. lack of std::map<K,V>::merge()).

## Building

A standard installation into /usr/local:

```bash
bash$> ./autogen.sh
bash$> ./configure
bash$> make && make install
```

Pass --prefix=path to configure or use DESTDIR for make install to install in non-standard locations.

## Getting started

See the examples directory for complete code ready to be run.

## License

This library is released under LGPL-3.0 and can be linked and used with commercial applications.

## Bug report & suggestions

Please see the AUTHORS file for contact information. Feel free to submit bug reports and suggestions.
