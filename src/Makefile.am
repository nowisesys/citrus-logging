EXTRA_DIST = libcitrus-logging.pc.in libcitrus-logging.pc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcitrus-logging.pc

otherincludedir = $(includedir)/citrus
otherinclude_HEADERS = logging.hpp

lib_LTLIBRARIES = libcitrus-logging.la
libcitrus_logging_la_SOURCES = logging.hpp logging.cpp \
    logger.cpp message.cpp datetime.cpp format.cpp \
    record.cpp sender.cpp target.cpp \
    target/file.cpp target/stream.cpp target/syslog.cpp \
    format/text.cpp format/json.cpp format/csv.cpp \
    format/sql.cpp format/escape.cpp format/escape.hpp \
    format/zero.cpp format/prefix.cpp

libcitrus_logging_la_LDFLAGS  = -version-info 1:0:0
libcitrus_logging_la_CXXFLAGS = -DLIBSOCKPP_EXPORTS=1
