/****
COMMON; arch.h, CPU architecture header

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
