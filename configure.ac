AC_PREREQ([2.69])
AC_INIT([Commoner], [1.0.0], [amagura28@gmail.com],,[https://github.com/amagura/common/issues])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign -Wall])
LT_INIT


AC_USE_SYSTEM_EXTENSIONS

# Check for programs
AC_PROG_CC
AC_PROG_INSTALL

# FIXME: Replace `main' with a function in `-lcheck':
AC_CHECK_LIB([check], [main])

# Checks for header files
AC_CHECK_HEADERS([limits.h stdint.h stdlib.h string.h unistd.h])

# Check for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero memmove mempcpy memset strchr strdup strol])

# Produce output.
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT