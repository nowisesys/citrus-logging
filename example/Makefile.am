AM_CPPFLAGS = -I../src
LIBADD = -L../src -lcitrus-logging

noinst_PROGRAMS = \
    simple logger message datetime sender level \
    record \
    format-text format-json format-sql \
    target-file target-stream target-syslog

simple_SOURCES = simple.cpp
simple_LDADD = ../src/libcitrus-logging.la

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

format_text_SOURCES = format-text.cpp
format_text_LDADD = ../src/libcitrus-logging.la

format_json_SOURCES = format-json.cpp
format_json_LDADD = ../src/libcitrus-logging.la

format_sql_SOURCES = format-sql.cpp
format_sql_LDADD = ../src/libcitrus-logging.la

target_file_SOURCES = target-file.cpp
target_file_LDADD = ../src/libcitrus-logging.la

target_stream_SOURCES = target-stream.cpp
target_stream_LDADD = ../src/libcitrus-logging.la

target_syslog_SOURCES = target-syslog.cpp
target_syslog_LDADD = ../src/libcitrus-logging.la
