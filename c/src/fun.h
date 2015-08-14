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
#ifndef COMMON_FUN_H_GUARD
# define COMMON_FUN_H_GUARD 1
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

# include "mac.h"

/** cpeek: access the character either before or after the current character
 ** in an array of characters.  **/
char cpeek PARAMS((const char *c, const char *s, const short fwd));

# include "intlen.h"

# include "rev.h"

# include "itoa.h"

# include "concat.h"

# if 0
/** concatl: catenate as many _s_ource strings into `buf'
 ** as will fit in `bufsiz' bytes **/
/** XXX if you _must_ use concatl directly: be sure to pass `(void *)NULL' as
 ** the last argument **/
size_t concatl PARAMS((char *buf, size_t bufsiz, const char *s1, ...));
# undef catl
# define catl(...) (concatl(__VA_ARGS__, (void *)NULL))
# endif

/** repeat: create an array of chars containing n-1 many _s_ chars **/
void repeat PARAMS((char *dst, const char s, size_t n));
# if COM_TESTING
int strrep PARAMS((char *dst, const char *s, size_t n));
char *strprep PARAMS((const char *s, int x));
# endif

/** strndelim: counts number of delimiters within a given string **/
int *strndelim PARAMS((const char *s, const char od, const char cd, int count[2]));

/** strwodq: remove double quotes from a string **/
int strwodq PARAMS((char *dst, const char *src, size_t n));
char *strwodqp PARAMS((const char *src));

END_C_DECLS

#endif /* COMMON_FUN_H_GUARD */
