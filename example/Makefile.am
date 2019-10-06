AM_CPPFLAGS = -I../src
LIBADD = -L../src -lcitrus-logging

lib_LIBRARIES = libsupport.a
libsupport_a_SOURCES = support.cpp support.hpp

noinst_PROGRAMS = \
    logger message datetime sender level record derived \
    hostname \
    format-text format-json format-sql format-csv \
    format-prefix format-zero format-user format-xml \
    format-column format-string \
    target-file target-stream target-syslog target-http \
    target-smtp \
    utils-uuid utils-escape

logger_SOURCES = logger.cpp
logger_LDADD = ../src/libcitrus-logging.la

message_SOURCES = message.cpp
message_LDADD = ../src/libcitrus-logging.la

datetime_SOURCES = datetime.cpp
datetime_LDADD = ../src/libcitrus-logging.la

sender_SOURCES = sender.cpp
sender_LDADD = ../src/libcitrus-logging.la

level_SOURCES = level.cpp
level_LDADD = ../src/libcitrus-logging.la

record_SOURCES = record.cpp
record_LDADD = ../src/libcitrus-logging.la

derived_SOURCES = derived.cpp derived.hpp
derived_LDADD = ../src/libcitrus-logging.la libsupport.a

hostname_SOURCES = hostname.cpp
hostname_LDADD = ../src/libcitrus-logging.la libsupport.a

format_text_SOURCES = format-text.cpp 
format_text_LDADD = ../src/libcitrus-logging.la libsupport.a

format_json_SOURCES = format-json.cpp 
format_json_LDADD = ../src/libcitrus-logging.la libsupport.a

format_sql_SOURCES = format-sql.cpp 
format_sql_LDADD = ../src/libcitrus-logging.la libsupport.a

format_csv_SOURCES = format-csv.cpp 
format_csv_LDADD = ../src/libcitrus-logging.la libsupport.a

format_prefix_SOURCES = format-prefix.cpp 
format_prefix_LDADD = ../src/libcitrus-logging.la libsupport.a

format_zero_SOURCES = format-zero.cpp 
format_zero_LDADD = ../src/libcitrus-logging.la libsupport.a

format_user_SOURCES = format-user.cpp 
format_user_LDADD = ../src/libcitrus-logging.la libsupport.a

format_xml_SOURCES = format-xml.cpp 
format_xml_LDADD = ../src/libcitrus-logging.la libsupport.a

format_column_SOURCES = format-column.cpp 
format_column_LDADD = ../src/libcitrus-logging.la libsupport.a

format_string_SOURCES = format-string.cpp 
format_string_LDADD = ../src/libcitrus-logging.la libsupport.a

target_file_SOURCES = target-file.cpp
target_file_LDADD = ../src/libcitrus-logging.la libsupport.a

target_stream_SOURCES = target-stream.cpp
target_stream_LDADD = ../src/libcitrus-logging.la libsupport.a

target_syslog_SOURCES = target-syslog.cpp
target_syslog_LDADD = ../src/libcitrus-logging.la libsupport.a

target_http_SOURCES = target-http.cpp
target_http_LDADD = ../src/libcitrus-logging.la libsupport.a

target_smtp_SOURCES = target-smtp.cpp
target_smtp_LDADD = ../src/libcitrus-logging.la libsupport.a

utils_uuid_SOURCES = utils-uuid.cpp
utils_uuid_LDADD = ../src/libcitrus-logging.la @UUID_LIBS@
utils_uuid_CPPFLAGS = $(AM_CPPFLAGS) @UUID_CFLAGS@

utils_escape_SOURCES = utils-escape.cpp
utils_escape_LDADD = ../src/libcitrus-logging.la
