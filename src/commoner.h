/****
  COMMON; commoner.h

  Copyright (C) 2015, 2016, 2017 Alexej G. Magura

  This file is a part of Commoner

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
#ifndef COMMONER_COMMONER_H_GUARD
# define COMMONER_COMMONER_H_GUARD 1
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

# if HAVE_CONFIG_H
#  include <config.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

/////////////////////////////////////////
// PUBLIC Macros
/////////////////////////////////////////
# define catl(...) (concatl(__VA_ARGS__, (void *)NULL))
# define catm(...) (concatm(__VA_ARGS__, (void *)NULL))

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

//# if !defined(COM_DEBUG)
#  define COM_DEBUG 3 // XXX change this to turn debug messages on/off
//# endif

# if COM_DEBUG
#  if !defined(COM_DLVL)
#   define COM_DLVL (COM_DEBUG + 1) // XXX change this to increase/decrease debug verbosity
#  endif
# endif

# if COM_DEBUG || COMNR_INTERNAL_DEBUG
#  if defined(_GNU_SOURCE)
#   include <mcheck.h>
#  endif
#  define COM_DBG(format, ...)					\
     do {							\
	  fprintf(stderr, "## (%s)(%s)%d\n",			\
		  COMNR_PROGNAME, __FILE__, __LINE__);		\
	  fprintf(stderr, "#  `%s'\n", __FUNCTION__);		\
	  fprintf(stderr, (format), ##__VA_ARGS__);		\
	  fprintf(stderr, "\n");	       			\
     } while(0)
#  define COMNR_SDBG(format, exp)				\
     do {						\
	  fprintf(stderr, "## (%s)(%s)%d\n",		\
		  COMNR_PROGNAME, __FILE__, __LINE__);	\
	  fprintf(stderr, "#  `%s`\n", __FUNCTION__);	\
	  fprintf(stderr, (format), (exp));		\
	  fprintf(stderr, "\n");			\
     } while(0)
#  define COMNR_ONDBG(...) (__VA_ARGS__)
#  define COMNR_XONDBG(COMNR_X) COMNR_X
void com_ping PARAMS((void));
void com_pong PARAMS((void));
#  define com_ping COMNR_DBG("\n^^^^ %s ^^^^\n", "MARCO!")
#  define com_pong COMNR_DBG("\n$$$$ %s $$$$\n", "POLO!")
#  define com_neko(COMNR_F, ...)				\
     do {						\
	  fprintf(stderr,				\
		  "\n%s{neko-chan}%s(%s)(%s)(%d)\n",	\
		  "\033[91m❤\033[0m",		\
		  "\033[91m❤\033[0m",		\
		  __FILE__, __FUNCTION__, __LINE__);	\
	  fprintf(stderr, "%s%s%s, %s%s%s~\n",		\
		  "\033[32mn",				\
		  "\033[35my",				\
		  "\033[31ma\033[0m",			\
		  "\033[32mn",				\
		  "\033[35my",				\
		  "\033[31ma\033[33ma\033[0m");		\
	  fprintf(stderr, (COMNR_F), ##__VA_ARGS__);	\
	  fprintf(stderr, "\n");			\
     } while(0)
# else
#  define COMNR_DBG(format, ...)
#  define COMNR_SDBG(format, exp)
#  define COMNR_ONDBG(...)
#  define COMNR_XONDBG(COMNR_X)
#  define com_ping
#  define com_pong
#  define com_neko(COMNR_F, ...)
# endif

# define COMNR_ERROR(format, ...)				\
     do {						\
	  fprintf(stderr, "%s:err: ", COMNR_PROGNAME);	\
	  fprintf(stderr, (format), __VA_ARGS__);	\
	  fprintf(stderr,				\
		  "\nin %s:{%d}:%s()\n",		\
		  __FILE__,				\
		  __LINE__,				\
		  __FUNCTION__);			\
     } while(0)

# define COMNR_FATAL(...)			\
     do {				\
	  fprintf(stderr,		\
		  "%s: %s\n",		\
		  (COMNR_PROGNAME),	\
		  ##__VA_ARGS__);	\
	  exit(EXIT_FAILURE);		\
     } while (0)

# define com_usage(format) (printf((format), (COMNR_PROGNAME)));

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
#  define COMNR_STRTONUM(dst_num, const_string)			\
     do {							\
	  errno = 0;						\
	  ((dst_num) = strtonum((const_string),			\
				INT_MIN,			\
				INT_MAX,			\
				NULL));				\
	  if (errno != 0) {					\
	       perror(COMNR_PROGNAME);				\
	       exit(EXIT_FAILURE);				\
	  }							\
     } while(0)
# else
#  define COMNR_STRTONUM(dst_num, const_string)			\
     do {							\
	  errno = 0;						\
	  ((dst_num) = strtol((const_string), NULL, 10));	\
	  if (errno != 0) {					\
	       perror(COMNR_PROGNAME);				\
	       exit(EXIT_FAILURE);				\
	  }							\
     } while(0)
# endif

# if !defined(HAVE_BZERO)
#  define bzero(COMNR_B, COMNR_LEN)						\
     (memset((void *)(COMNR_B), '\0', (size_t)(COMNR_LEN)), (void)0)
# endif

# if !defined(HAVE_BCOPY)
#  define bcopy(COMNR_B1, COMNR_B2, COMNR_LEN)				\
     (memmove((void *)(COMNR_B2),					\
	      (const void *)(COMNR_B1),					\
	      (size_t)(COMNR_LEN)),					\
      (void)0)
# endif

# if !defined(HAVE_MEMPCPY)
#  define mempcpy(COMNR_D, COMNR_S, COMNR_L)		\
     (memcpy((void *)(COMNR_D),				\
	     (const void *)(COMNR_S),			\
	     (size_t)(COMNR_L))				\
      + (size_t)(COMNR_L))
# endif

# define mempmove(COMNR_D, COMNR_S, COMNR_L)		\
     (memmove((void *)(COMNR_D),			\
	      (const void *)(COMNR_S),			\
	      (size_t)(COMNR_L))			\
      + (size_t)(COMNR_L))

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

/////////////////////////////////////////
// PUBLIC Functions
/////////////////////////////////////////

/** functions hosted by str.c **/

/* from defunct mem.c */
int memlen PARAMS((const char *s));
char *strterm PARAMS((char *s, size_t sz));

const char *strend PARAMS((const char *const s0));
# if defined(COMNR_EXPOSE_OLD_CPEEK)
char old_cpeek PARAMS((const char *c, const char *s, const short fwd));
# endif
char cpeek PARAMS((const char *const sp0, const char *const head));

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

/** functions hosted by int.c **/
uintmax_t uintm_len PARAMS((uintmax_t idx));
int intlen PARAMS((int idx));
int intlenc PARAMS((const int idx));
size_t intlenm PARAMS((int src));

/* from defunct itoa.c */
void itoa PARAMS((char *dst, int src));
char *itoap PARAMS((const int src));

/** functions hosted by os.c **/
char *subdir PARAMS((char **dirs, size_t ssz));
int rpath PARAMS((char *pth));
int direxists PARAMS((char *pth));
size_t flen PARAMS((FILE *fp));


END_C_DECLS

#endif /* COMMONER_COMMONER_H_GUARD */
