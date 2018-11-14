AC_PREREQ([2.69])
AC_INIT([Commoner], [0.1.20], [amagura28@gmail.com],,[https://github.com/amagura/common/issues])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_USE_SYSTEM_EXTENSIONS

AM_INIT_AUTOMAKE([foreign])
AM_PROG_AR

LT_INIT

# Check for programs
AC_PROG_CC
AC_PROG_AWK
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_CXX
LT_INIT

# Checks for header files
AC_CHECK_HEADERS([fcntl.h limits.h stdint.h stdlib.h string.h strings.h sys/time.h unistd.h mcheck.h])


# Check for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bcopy bzero gettimeofday memmove mempcpy memset pow realpath strchr strdup strncasecmp strrchr strstr strtol])
AC_SEARCH_LIBS([strtonum],
               [bsd],
               [AC_DEFINE([HAVE_STRTONUM], [1], [Define to 1 if you have the 'strtonum' function])])
AC_SEARCH_LIBS([strlcpy],
               [bsd],
               [AC_DEFINE([HAVE_STRLCPY], [1], [Define to 1 if you have the 'strlcpy' function])])
AC_SEARCH_LIBS([strlcat],
               [bsd],
               [AC_DEFINE([HAVE_STRLCAT], [1], [Define to 1 if you have the 'strlcat' function])])
AC_SEARCH_LIBS([getline],
               [c],
               [AC_DEFINE([HAVE_GETLINE], [1], [Define to 1 if you have the 'getline' function])])
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
     AC_DEFINE([COMNR_INTERNAL_DEBUG], [1], [filler description])
fi

AC_DEFINE([COMNR_PROGNAME], [PACKAGE], [legacy macro used by a lot of debug macros in commoner])

AM_CONDITIONAL([DEBUG], [test "x$debug" = "xtrue"])
AM_CONDITIONAL([NO_DEBUG], [test "x$debug" != "xtrue"])

# Produce output.
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])
AC_OUTPUT
