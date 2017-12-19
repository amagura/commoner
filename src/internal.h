/****
  COMMON; internal.h

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
#ifndef COMMONER_INTERNAL_H_GUARD
# define COMMONER_INTERNAL_H_GUARD 1
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

# include <string.h>

# if COINT_INTERNAL_DEBUG
#  if !defined(COINT_INTERNAL_DLVL)
#   define COINT_INTERNAL_DLVL (COINT_INTERNAL_DEBUG + 1) // XXX change this to increase/decrease debug verbosity
#  endif
# endif

# if defined(COINT_INTERNAL_DEBUG)
#  define COINT_DBG(COINT_format, ...)					\
     do {								\
	  fprintf(stderr, "## (%s)(%s)%d\n",				\
		  COINT_PROGNAME, __FILE__, __LINE__);			\
	  fprintf(stderr, "#  `%s'\n", __FUNCTION__);			\
	  fprintf(stderr, (COINT_format), ##__VA_ARGS__);		\
	  fprintf(stderr, "\n");					\
     } while(0)
#  define COINT_SDBG(COINT_format, COINT_exp)				\
     do {								\
	  fprintf(stderr, "## (%s)(%s)%d\n",				\
		  COINT_PROGNAME, __FILE__, __LINE__);			\
	  fprintf(stderr, "#  `%s`\n", __FUNCTION__);			\
	  fprintf(stderr, (COINT_format), (COINT_exp));			\
	  fprintf(stderr, "\n");					\
     } while(0)
#  define COINT_ONDBG(...) (__VA_ARGS__)
#  define COINT_XONDBG(COINT_X) (COINT_X)
#  define coint_ping COINT_DBG("\n^^^^ %s ^^^^\n", "MARCO!")
#  define coint_pong COINT_DBG("\n$$$$ %s $$$$\n", "POLO!")
#  define coint_neko(COINT_F, ...)				\
     do {							\
	  fprintf(stderr,					\
		  "\n%s{neko-chan}%s(%s)(%s)(%d)\n",		\
		  "\033[91m❤\033[0m",				\
		  "\033[91m❤\033[0m",				\
		  __FILE__, __FUNCTION__, __LINE__);		\
	  fprintf(stderr, "%s%s%s, %s%s%s~\n",			\
		  "\033[32mn",					\
		  "\033[35my",					\
		  "\033[31ma\033[0m",				\
		  "\033[32mn",					\
		  "\033[35my",					\
		  "\033[31ma\033[33ma\033[0m");			\
	  fprintf(stderr, (COINT_F), ##__VA_ARGS__);		\
	  fprintf(stderr, "\n");				\
     } while(0)

/* FIXME both commoner.h and internal.h define these macro
 * as empty when COINT_INTERNAL_DEBUG and COINT_EXTERNAL_DEBUG are not defined.
 * These macros should be defined in a common source that both can use.
 */
# endif

END_C_DECLS

#endif /* COMMONER_INTERNAL_H_GUARD */
