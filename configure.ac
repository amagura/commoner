AC_PREREQ([2.69])
AC_INIT([Commoner], [0.1.13], [amagura28@gmail.com],,[https://github.com/amagura/common/issues])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_USE_SYSTEM_EXTENSIONS

AM_INIT_AUTOMAKE([foreign -Wall])
AM_PROG_AR

LT_INIT

# Check for programs
AC_PROG_CC
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for header files
AC_CHECK_HEADERS([mcheck.h limits.h stdint.h stdlib.h string.h unistd.h])

# Check for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero bcopy memmove mempcpy memset realpath strchr strdup strtol])
AC_SEARCH_LIBS([strtonum],
               [bsd],
               [AC_DEFINE([HAVE_STRTONUM], [1], [needs a description because the people at GNU are fucking morons])])
#########
# Options
#########
AC_ARG_ENABLE([debug],
              [  --enable-debug		turn on debugging (default: disabled)],
              [case "${enableval}" in
               yes) debug=true ;;
               no) debug=false ;;
               *) AC_MSG_WARN([bad value '${enableval}' for --enable-debug]) ;;
             esac],[debug=no])

if test "x$debug" = "xtrue"; then
  AC_DEFINE([COMNR_INTERNAL_DEBUG], [1], [needs a description because fuck])
fi

AC_DEFINE([COMNR_PROGNAME], [PACKAGE], [legacy macro used by a lot of debug macros in commoner])

AM_CONDITIONAL([DEBUG], [test "x$debug" = "xtrue"])
AM_CONDITIONAL([NO_DEBUG], [test "x$debug" != "xtrue"])

# Produce output.
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
