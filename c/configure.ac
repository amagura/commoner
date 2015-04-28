#  Copyright 2015 Alexej Magura
#
#  Copying and distribution of this file, with or without modification,
#  are permitted in any medium without royalty provided the copyright
#  notice and this notice are preserved.  This file is offered as-is,
#  without any warranty.
AC_PREREQ([2.65])
AC_INIT([Common], [1.0], [agm2819@gmail.com],,[https://github.com/amagura/common])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_USE_SYSTEM_EXTENSIONS

# Check for compilers
dnl C
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CPP

AC_SEARCH_LIBS([abs], [m],,[AC_MSG_ERROR([Please use a C99 compliant compiler])])

# Check if peeps want to try to compile to native (compiler may or may not support it)
AC_ARG_ENABLE([native],
              AS_HELP_STRING([--enable-native], [enable processor-model specific compilation (default: enabled)]),
              [case "${enableval}" in
               yes) native=true ;;
               no) native=false ;;
               *) AC_MSG_ERROR([bad value ${enableval} for --enable-native]) ;;
             esac],[native=true])
AM_CONDITIONAL([NATIVE], [test "x$native" = "xtrue"])

# Check if peeps want to try to compile to generic (compiler may or may not support it)
AC_ARG_ENABLE([generic],
              AS_HELP_STRING([--enable-generic], [enable processor-family specific compilation (default: disabled)]),
              [case "${enableval}" in
               yes) generic=true ;;
               no) generic=false ;;
               *) AC_MSG_ERROR([bad value ${enableval} for --enable-generic]) ;;
             esac],[generic=false])
AM_CONDITIONAL([GENERIC], [test "x$generic" = "xtrue"])

# Check for debug
AC_ARG_ENABLE([debug],
              [  --enable-debug         turn on debugging (default: disabled)],
              [case "${enableval}" in
               yes) debug=true ;;
               no) debug=false ;;
               *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
             esac],[debug=no])
[test "x$debug" = "xno" && no_debug=false]
[test "x$debug" = "xfalse" && no_debug=true]

# Check for testdir
AC_ARG_ENABLE([testdir],
		[  --enable-testdir	defines ZB_ACPI_ROOT for testing (default: disabled)],
		[case "${enableval}" in
		 yes) testdir=true ;;
		 no) testdir=false ;;
		 *) AC_MSG_ERROR([bad value ${enableval} for --enable-testdir]) ;;
		 esac],[testdir=false])

AM_CONDITIONAL([TEST], [test "x$testdir" = "xtrue"])
AM_CONDITIONAL([DEBUG], [test "x$debug" = "xtrue"])
AM_CONDITIONAL([NO_DEBUG], [test "x$no_debug" = "xtrue"])

# Check for static compilation
AC_ARG_ENABLE([static],
	      AS_HELP_STRING([  --enable-static	turn on static compilation (default: disabled)]),
	      [case "${enableval}" in
	       yes) static=true ;;
	       no) static=false ;;
	       *) AC_MSG_ERROR([bad value ${enableval} for --enable-static]) ;;
	      esac],[static=false])

AM_CONDITIONAL([STATIC], [test "x$static" = "xtrue"])
AM_CONDITIONAL([GENERIC], [test "x$static" = "xtrue" || test "x$generic" = "xtrue"])
AM_CONDITIONAL([NATIVE], [test "x$static" = "xfalse" || test "x$native" = "xtrue"])

# generic?
m4_define([CLANG], [test "x`($CC -E -w -P -nostdinc - <<EOF
__clang__
EOF
)`" = "x1"])
m4_define([TINYC], [test ! "x`($CC -E -w -P -nostdinc - <<EOF
__TINYC__
EOF
)`" = "x__TINYC__"])
AM_CONDITIONAL([CPU_KNOWN], [test ! "x]CPUARCH[" = "x" && test ! "x]CPUARCH[" = "xunknown" && (]CLANG[ || ]TINYC[)])
AC_SUBST(CPUTYPE, CPUARCH)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
