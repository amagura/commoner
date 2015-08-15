/****
Copyright 2015 Alexej Magura

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****/
#ifndef COMMON_COMMON_H_GUARD
# define COMMON_COMMON_H_GUARD 1
/* BEGIN_C_DECLS should be used at the beginning of your declarations,
so that C++ compilers don't mangle their names.  Use END_C_DECLS at
the end of C declarations. */
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
#else
# define BEGIN_C_DECLS /* empty */
# define END_C_DECLS /* empty */
#endif

/* PARAMS is a macro used to wrap function prototypes, so that
  compilers that don't understand ANSI C prototypes still work,
  and ANSI C compilers can issue warnings about type mismatches. */
#undef PARAMS
#if defined (__STDC__) || defined (_AIX) \
       || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
       || defined(WIN32) || defined(__cplusplus)
# define PARAMS(protos) protos
#else
# define PARAMS(protos) ()
#endif

BEGIN_C_DECLS

# include <stdio.h>
# include <stdlib.h>

#include "arch.h"
#include "os.h"
#include "cc.h"

# if (defined(COM_CHECK)			\
      && COM_CHECK				\
      && defined(_GNU_SOURCE))
#  include <mcheck.h>
#  define com_mtrace	\
     do {		\
	  mtrace();	\
     } while(0)
#  define com_muntrace	\
     do {		\
	  muntrace();	\
     } while(0)
# else
#  define com_mtrace
#  define com_muntrace
# endif

# if !defined(COM_INCLUDE_STRING_H)
#  define COM_INCLUDE_STRING_H 0
# endif

# if COM_INCLUDE_STRING_H
#  include <string.h>
# else
void *memset PARAMS((void *s, int c, size_t n));
void *memcpy PARAMS((void *dest, const void *src, size_t n));
void *memmove PARAMS((void *dest, const void *src, size_t n));
char *strchr PARAMS((const char *s, int c));
# endif

# if !defined(COM_TESTING)
#  define COM_TESTING 0 /* use this to enable functions that are not yet deemed stable */
# endif

# if !defined(COM_DEBUG)
#  define COM_DEBUG 0 // XXX change this to turn debug messages on/off
# endif

# if COM_DEBUG
#  if !defined(COM_DLVL)
#   define COM_DLVL (COM_DEBUG + 1) // XXX change this to increase/decrease debug verbosity
#  endif
# endif

# if !defined(PACKAGE_VERSION)
#  define PACKAGE_VERSION ""
# endif

# if !defined(PACKAGE)
#  define PACKAGE "common"
# endif

# if !defined(COM_PROGNAME)
#  define COM_PROGNAME PACKAGE
# endif

# if COM_DEBUG
#  if defined(_GNU_SOURCE)
#   include <mcheck.h>
#  endif
#  define COM_DBG(format, ...)					\
     do {							\
	  fprintf(stderr, "## (%s)(%s)%d\n",			\
		  COM_PROGNAME, __FILE__, __LINE__);		\
	  fprintf(stderr, "#  `%s'\n", __FUNCTION__);		\
	  fprintf(stderr, (format), ##__VA_ARGS__);		\
	  fprintf(stderr, "\n");	       			\
     } while(0)
#  define COM_SDBG(format, exp)				\
     do {						\
	  fprintf(stderr, "## (%s)(%s)%d\n",		\
		  COM_PROGNAME, __FILE__, __LINE__);	\
	  fprintf(stderr, "#  `%s`\n", __FUNCTION__);	\
	  fprintf(stderr, (format), (exp));		\
	  fprintf(stderr, "\n");			\
     } while(0)
#  define COM_ONDBG(...) (__VA_ARGS__)
#  define COM_XONDBG(COM_X) COM_X
#  define com_ping COM_DBG("\n^^^^ %s ^^^^\n", "MARCO!")
#  define com_pong COM_DBG("\n$$$$ %s $$$$\n", "POLO!")
#  define com_neko(COM_F, ...)				\
     do {						\
	  fprintf(stderr,				\
		  "\n%s{neko-chan}%s(%s)(%s)(%d)\n",	\
		  "\033[91m❤\033[0m",			\
		  "\033[91m❤\033[0m",			\
		  __FILE__, __FUNCTION__, __LINE__);	\
	  fprintf(stderr, "%s%s%s, %s%s%s~\n",		\
		  "\033[32mn",				\
		  "\033[35my",				\
		  "\033[31ma\033[0m",			\
		  "\033[32mn",				\
		  "\033[35my",				\
		  "\033[31ma\033[33ma\033[0m");		\
	  fprintf(stderr, (COM_F), ##__VA_ARGS__);	\
	  fprintf(stderr, "\n");			\
     } while(0)
# else
#  define COM_DBG(format, ...)
#  define COM_SDBG(format, exp)
#  define COM_ONDBG(...)
#  define COM_XONDBG(COM_X)
#  define com_ping
#  define com_pong
#  define com_neko(COM_F, ...)
# endif

# define COM_ERROR(format, ...)				\
     do {						\
	  fprintf(stderr, "%s:err: ", COM_PROGNAME);	\
	  fprintf(stderr, (format), __VA_ARGS__);	\
	  fprintf(stderr,				\
		  "\nin %s:{%d}:%s()\n",		\
		  __FILE__,				\
		  __LINE__,				\
		  __FUNCTION__);			\
     } while(0)

# define COM_FATAL(...)			\
     do {				\
	  fprintf(stderr,		\
		  "%s: %s\n",		\
		  (COM_PROGNAME),	\
		  ##__VA_ARGS__);	\
	  exit(EXIT_FAILURE);		\
     } while (0)

# define com_usage(format) (printf((format), (COM_PROGNAME)));

# define com_arg(opt, desc, tabs) (printf("  %s%s%s\n", (opt),(tabs),(desc)));

# define com_arg_eol_tabs "\n\t\t\t\t"
# define com_help(usage, tabs)				\
     do {						\
	  com_usage((usage));				\
	  com_arg("-h, --help",				\
		  "print this message and exit",	\
		  (tabs));				\
	  com_arg("-v, --version",			\
		  "print program version and exit",	\
		  (tabs));				\
     } while(0)

# if HAVE_LIBBSD
#  include <limits.h>
#  include <bsd/stdlib.h>
// FIXME, the following macros shouldn't call `exit' or `perror'.
#  define COM_STRTONUM(dst_num, const_string)			\
     do {							\
	  errno = 0;						\
	  ((dst_num) = strtonum((const_string),			\
				INT_MIN,			\
				INT_MAX,			\
				NULL));				\
	  if (errno != 0) {					\
	       perror(COM_PROGNAME);				\
	       exit(EXIT_FAILURE);				\
	  }							\
     } while(0)
# else
#  define COM_STRTONUM(dst_num, const_string)			\
     do {							\
	  errno = 0;						\
	  ((dst_num) = strtol((const_string), NULL, 10));	\
	  if (errno != 0) {					\
	       perror(COM_PROGNAME);				\
	       exit(EXIT_FAILURE);				\
	  }							\
     } while(0)
# endif

# ifndef bzero
#  define bzero(COM_B, COM_LEN)						\
     (memset((void *)(COM_B), '\0', (size_t)(COM_LEN)), (void)0)
# endif

# ifndef bcopy
#  define bcopy(COM_B1, COM_B2, COM_LEN)			\
     (memmove((void *)(COM_B2),					\
	      (const void *)(COM_B1),				\
	      (size_t)(COM_LEN)),				\
      (void)0)
# endif

# ifndef mempcpy
#  define mempcpy(COM_D, COM_S, COM_L)		\
     (memcpy((void *)(COM_D),			\
	     (const void *)(COM_S),		\
	     (size_t)(COM_L))			\
      + (size_t)(COM_L))
# endif

#  define mempmove(COM_D, COM_S, COM_L)		\
     (memmove((void *)(COM_D),			\
	      (const void *)(COM_S),		\
	      (size_t)(COM_L))			\
      + (size_t)(COM_L))

#if 0
inline int memlen(const char *s)
{
     char *a = NULL;
     int r;
     if ((a = strchr(s, '\0'))) {
	  r = (int)(a - s);
	  return r;
     }
#endif

END_C_DECLS

#endif /* COMMON_COMMON_H_GUARD */
