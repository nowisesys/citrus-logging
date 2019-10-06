EXTRA_DIST = libcitrus-logging.pc.in libcitrus-logging.pc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcitrus-logging.pc

otherincludedir = $(includedir)/citrus
otherinclude_HEADERS = logging.hpp

lib_LTLIBRARIES = libcitrus-logging.la
libcitrus_logging_la_SOURCES = logging.hpp logging.cpp \
    logger.cpp message.cpp datetime.cpp format.cpp \
    record.cpp sender.cpp target.cpp \
    utils/escape.cpp utils/escape.hpp utils/curl.hpp utils/curl.cpp \
    utils/uuid.cpp utils/uuid.hpp \
    target/file.cpp target/stream.cpp target/syslog.cpp \
    target/http.cpp target/smtp.cpp \
    format/text.cpp format/json.cpp format/csv.cpp \
    format/sql.cpp  format/zero.cpp format/prefix.cpp \
    format/user.cpp format/xml.cpp format/column.cpp \
    format/string.cpp

libcitrus_logging_la_LDFLAGS  = -version-info 1:0:0 @LIBCURL@ @UUID_LIBS@
libcitrus_logging_la_CXXFLAGS = -DLIBCITRUS_EXPORTS=1 @LIBCURL_CPPFLAGS@ @UUID_CFLAGS@
