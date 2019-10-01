#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libcitrus-logging], [1.0.0], [bugs@nowise.se])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE(1.16.1 subdir-objects)

AC_LANG([C++])
AX_CXX_COMPILE_STDCXX(17)

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([string.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([putenv])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/libcitrus-logging.pc
                 example/Makefile])
AC_OUTPUT
