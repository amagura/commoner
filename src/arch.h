/* vim: set ft=c: */
/****
  COMMON; arch.h, CPU architecture header

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
#ifndef COMMON_COMPAT_ARCH_H_GUARD
# define COMMON_COMPAT_ARCH_H_GUARD 1
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

# if !defined(COMNR__HPPA)
#  if defined(__hppa__)		\
     || defined(__HPPA__)	\
     || defined(__hppa)
#   define COMNR__HPPA 1
#  else
#   define COMNR__HPPA 0
#  endif
# endif

# if !defined(COMNR__SYSZ)
#  if defined(__370__)			\
     || defined(__THW_370__)		\
     || defined(__s390__)		\
     || defined(__s390x__)		\
     || defined(__zarch__)		\
     || defined(__SYSC_ZARCH__)
#   define COMNR__SYSZ 1
#  else
#   define COMNR__SYSZ 0
#  endif
# endif

# if !defined(COMNR__SPARC)
#  if defined(__sparc__) \
     || defined(__sparc)
#   define COMNR__SPARC 1
#  else
#   define COMNR__SPARC 0
#  endif
# endif

// Power PC
# if !defined(COMNR__PPC)
#  if defined(__powerpc)			\
     || defined(__powerpc__)		\
     || defined(__powerpc64__)	\
     || defined(__POWERPC__)		\
     || defined(__ppc__)			\
     || defined(__ppc64__)		\
     || defined(__PPC__)			\
     || defined(__PPC64__)		\
     || defined(_ARCH_PPC)		\
     || defined(_ARCH_PPC64)		\
     || defined(_M_PPC)			\
     || defined(_ARCH_PPC)		\
     || defined(_ARCH_PPC64)		\
     || defined(__ppc)
#   define COMNR__PPC 1
#  else
#   define COMNR__PPC 0
#  endif
# endif

# if !defined(COMNR__MIPS)
#  if defined(__mips__) 		\
     || defined(mips) 		\
     || defined(__mips)		\
     || defined(__MIPS__)
#   define COMNR__MIPS 1
#  else
#   define COMNR__MIPS 0
#  endif
# endif

// Motorola 68k
# if !defined(COMNR__M68K)
#  if defined(__m68k__) 		\
     || defined(M68000) 		\
     || defined(__MC68K__)
#   define COMNR__M68K 1
#  else
#   define COMNR__M68K 0
#  endif
# endif

# if !defined(COMNR__IA64)
#  if defined(__ia64__)		\
     || defined(_IA64)		\
     || defined(__IA64__)	\
     || defined(__ia64)		\
     || defined(_M_IA64)		\
     || defined(__itanium__)
#   define COMNR__IA64 1
#  else
#   define COMNR__IA64 0
#  endif
# endif

# if !defined(COMNR__arm)
#  if defined(__arm__)      			\
     || defined(__thumb__)  			\
     || defined(__TARGET_ARCH_ARM) 	\
     || defined(__TARGET_ARCH_THUMB)	\
     || defined(_ARM)				\
     || defined(_M_ARM)				\
     || defined(_M_ARMT)				\
     || defined(__arm)
#   define COMNR__ARM 1
#  else
#   define COMNR__ARM 0
#  endif
# endif

# if !defined(COMNR__ARM64)
#  if defined(__arch64__)
#   define COMNR__ARM64 1
#  else
#   define COMNR__ARM64 0
#  endif

# if !defined(COMMON_alpha)
#  if defined(__alpha__) \
     || defined(__alpha) \
     || defined(_M_ALPHA)
#   define COMMON_alpha 1
#  else
#   define COMMON_alpha 0
#  endif
# endif

# if !defined(COMMON_amd64)
#  if defined(__amd64__)     \
     || defined(__amd64)     \
     || defined(__x86_64__)  \
     || defined(__x86_64)    \
     || defined(_M_X64)	     \
     || defined(_M_AMD64)
#   define COMMON_amd64 1
#  else
#   define COMMON_amd64 0
#  endif
# endif

# if !defined(COMMON_x86)
#  if defined(i386)		\
     || defined(__i386)		\
     || defined(__i386__)	\
     || defined(__i486__)	\
     || defined(__i586__)	\
     || defined(__i686__)	\
     || defined(__IA32__)	\
     || defined(_M_I86)		\
     || defined(_M_IX86)	\
     || defined(__X86__)	\
     || defined(_X86_)		\
     || defined(__THW_INTEL__) 	\
     || defined(__I86__)	\
     || defined(__INTEL__)	\
     || defined(__386)
#   define COMMON_x86 1
#  else
#   define COMMON_x86 0
#  endif
# endif

END_C_DECLS

#endif /* COMMMON_COMPAT_H_GUARD */
