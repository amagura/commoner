/****
  COMMON; common.h

  Copyright (C) 2015, 2016, 2017 Alexej G. Magura

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
****/
#ifndef COMMON_COMMON_H_GUARD
# define COMMON_COMMON_H_GUARD 1
/* BEGIN_C_DECLS should be used at the beginning of your declarations,
so that C++ compilers don't mangle their names.  Use END_C_DECLS at
the end of C declarations. */
# undef BEGIN_C_DECLS
# undef END_C_DECLS
# ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS }
# else
#  define BEGIN_C_DECLS /* empty */
#  define END_C_DECLS /* empty */
# endif

/* PARAMS is a macro used to wrap function prototypes, so that
  compilers that don't understand ANSI C prototypes still work,
  and ANSI C compilers can issue warnings about type mismatches. */
# undef PARAMS
# if defined (__STDC__) || defined (_AIX) \
       || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
       || defined(WIN32) || defined(__cplusplus)
#  define PARAMS(protos) protos
# else
#  define PARAMS(protos) ()
# endif

BEGIN_C_DECLS

# include <stdio.h>
# include <stdlib.h>

/////////////////////////////////////////
// PUBLIC Functions
/////////////////////////////////////////

/** functions hosted by str.c **/

/* from defunct mem.c */
int memlen PARAMS((const char *s));
char *strterm PARAMS((char *s, size_t sz));

const char *strend PARAMS((const char *const s0));
# if defined(COM_EXPOSE_OLD_CPEEK)
char old_cpeek PARAMS((const char *c, const char *s, const short fwd));
# endif
const char cpeek PARAMS((const char *const sp0, const char *const head));

/** functions hosted by repeat.c **/
void repeat PARAMS((char *dst, const char s, size_t n));
// XXX repeats strings instead of characters
int strrep PARAMS((char *dst, const char *s, size_t n));
char *strprep PARAMS((const char *s, int times));

/** functions hosted by rev.c **/
void rev PARAMS((char *s));
char *revp PARAMS((const char *s));
void revn PARAMS((char *s, size_t n));
char *revnp PARAMS((char *s, size_t n));

/** functions hosted by concat.c **/

/* it is worth noting that the original concat
 * is still available in concat.c
 * it is, however, commented out.
 */
size_t concatl PARAMS((char *dst, size_t sz, const char *s1, ...)) __attribute__((sentinel));
size_t concatm PARAMS((char *dst, size_t sz, const char *s1, ...)) __attribute__((sentinel));

/////////////////////////////////////////
// PUBLIC Macros
/////////////////////////////////////////

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

# if !defined(COM_USE_MEMPMOVE)
#  define COM_USE_MEMPMOVE 0
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
