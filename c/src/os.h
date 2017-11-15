/****
  COMMON; os.h

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
#ifndef COMMON_COMPAT_OS_H_GUARD
# define COMMON_COMPAT_OS_H_GUARD 1
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
#if defined (__STDC__) || defined (_AIX)		\
       || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
       || defined(WIN32) || defined(__cplusplus)
# define PARAMS(protos) protos
#else
# define PARAMS(protos) ()
#endif

BEGIN_C_DECLS

# if !defined(COMMON__WINDOWS)
#  if defined(__CYGWIN__)			\
     || defined(_WIN16)				\
     || defined(_WIN32)				\
     || defined(_WIN64)				\
     || defined(__WIN32__)			\
     || defined(__TOS_WIN__)			\
     || defined(__WINDOWS__)
#   define COMMON__WINDOWS 1
#  else
#   define COMMON__WINDOWS 0
#  endif
# endif

# if !defined(COMMON__BSD)
#  if defined(__NetBSD__)	   \
     || defined(__FreeBSD__)	   \
     || defined(__FreeBSD__kernel) \
     || defined(__DragonFly__)	   \
     || defined(__bsdi__)	   \
     || defined(__OpenBSD__)	   \
     || defined(_SYSTYPE_BSD)
#   define COMMON__BSD 1
#  else
#   define COMMON__BSD 0
#  endif
# endif

# if !defined(COMMON__LINUX)
#  if defined(__linux__)	\
     || defined(__gnu_linux__)
#   define COMMON__LINUX 1
#  else
#   define COMMON_LINUX 0
#  endif
# endif


END_C_DECLS

#endif /* COMMMON_COMPAT_OS_H_GUARD */
