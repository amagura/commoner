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

# if !defined(COMNR_INTERNAL_DEBUG)
#  undef COMNR_DBG
#  undef COMNR_SDBG
#  undef COMNR_ONDBG
#  undef COMNR_XONDBG
#  undef comnr_ping
#  undef comnr_pong
#  undef comnr_neko

#  define COMNR_DBG(COMNR_format, ...)
#  define COMNR_SDBG(COMNR_format, COMNR_exp)
#  define COMNR_ONDBG(...)
#  define COMNR_XONDBG(COMNR_X)
#  define comnr_ping
#  define comnr_pong
#  define comnr_neko
# endif

END_C_DECLS

#endif /* COMMONER_INTERNAL_H_GUARD */
