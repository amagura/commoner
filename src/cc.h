/****
  COMMON; cc.h, C compiler compatibility

  Copyright (C) 2015-2019 Alexej G. Magura

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
#ifndef COMMON_CCOMPILER_H_GUARD
# define COMMON_CCOMPILER_H_GUARD 1
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

# if !defined(COMNR__CC_GNUC)
#  if defined(__GNUC__)
#   define COMNR__CC_GNUC 1
#  else
#   define COMNR__CC_GNUC 0
#  endif
# endif

# if COMNR__CC_GNUC
#  define COMNR__CC 1
# endif

# if !defined(COMNR__CC_CLANG)
#  if defined(__clang__)
#   define COMNR__CC_CLANG 1
#  else
#   define COMNR__CC_CLANG 0
#  endif
# endif

# if COMNR__CC_CLANG
#  define COMNR__CC 2
# endif

# if !defined(COMNR__CC_TINYC)
#  if defined(__TINYC__) \
     || defined(__tinyc__)
#   define COMNR__CC_TINYC 1
#  else
#   define COMNR__CC_TINYC 0
#  endif
# endif

# if COMNR__CC_TINYC
#  define COMNR__CC 3
# endif

# if !defined(COMNR__CC_ARM)
#  if defined(__CC_ARM)
#   define COMNR__CC_ARM 1
#  else
#   define COMNR__CC_ARM 0
#  endif
# endif

# if COMNR__CC_ARM
#  define COMNR__CC 4
# endif

# if !defined(COMNR__CC_LCC)
#  if defined(__LCC__)
#   define COMNR__CC_LCC 1
#  else
#   define COMNR__CC_LCC 0
#  endif
# endif

# if !defined(COMNR__CC_LLVM)
#  if defined(__llvm__)
#   define COMNR__CC_LLVM 1
#  else
#   define COMNR__CC_LLVM 0
#  endif
# endif

# if COMNR__CC_LCC
#  define COMNR__CC 5
# endif

END_C_DECLS

#endif
