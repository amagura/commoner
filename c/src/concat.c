/****
COMMON; concat.c, (should be merged with similar files)

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
#ifndef COMMON_CONCAT_C_GUARD
# define COMMON_CONCAT_C_GUARD 1
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include "common.h"

# include "mem.c"

# if COM_DEBUG
#  include "cpeek.c"
# endif


// XXX OBSOLETE
# if 0
char *concat(const char *s1, ...) __attribute__((sentinel))
     __attribute__((warn_unused_result));

// XXX returned value needs free
char *concat(const char *s1, ...)
{
	va_list args;
	const char *s;
	char *p, *result;
	unsigned long l, m, n;
	m = n = strlen(s1);
	va_start(args, s1);
	while ((s = va_arg(args, char *))) {
		l = strlen(s);
		if ((m += l) < l) break;
	}
	va_end(args);
	if (s || m >= INT_MAX) return NULL;
	com_mtrace;

# if defined(__cplusplus)
	result = (char *)malloc(m + 1);
# else
	result = malloc(m + 1);
# endif
	if (!result) return NULL;

	memcpy(p = result, s1, n);
	p += n;
	va_start(args, s1);
	while ((s = va_arg(args, char *))) {
		l = strlen(s);
		if ((n += l) < l || n > m) break;
		memcpy(p, s, l);
		p += l;
	}
	va_end(args);
	if (s || m != n || p != result + n) {
		free(result);
		return NULL;
	}
	*p = '\0';
	com_muntrace;
	return result;
}
# endif

/* unlike `concat', which returns a
 * new pointer that must then be copied
 * or acted upon in some meaningfully meaningless
 * manner, `catl' returns the number of bytes belonging
 * to `buf', which could _NOT_ be filled, always copying
 * no more than `bufsiz` of data into `buf'
 *
 * If the return value is an integral value, which
 * we'll call `y', that is less than 0,
 * then the resulting catenation has been truncated by `!y'
 * many bytes.  Similarlly, if a positive value is returned:
 * `y' many bytes is how much of `buf', which was _NOT_ used.
 *
 * XXX A failure is indicated by a return value _equal to
 * the destination buffers size_, which may make errors somewhat
 * harder to spot! */

size_t concatl(char *dst, size_t sz, const char *s1, ...) __attribute__((sentinel));

size_t concatl(char *dst, size_t sz, const char *s1, ...)
{
     va_list args;
     const char *s = NULL;
     char *p, *tmp;
     unsigned long ldx, mdx, ndx;
     size_t used = 0;

     mdx = ndx = strlen(s1);
     va_start(args, s1);
     while ((s = va_arg(args, char *))) {
	  ldx = strlen(s);
	  if ((mdx += ldx) < ldx) break;
     }
     va_end(args);
     if (s || mdx >= INT_MAX) return sz;
     com_mtrace;
# if defined(__cplusplus)
     tmp = (char *)malloc(mdx + 1);
# else
     tmp = malloc(mdx + 1);
# endif
     if (!tmp) return sz;
     bzero(tmp, mdx + 1);
     bzero(dst, mdx + 1);

     p = tmp;
     p = mempcpy(p, (char *)s1, ndx);

     used += ndx;
     COM_DBG("p: `%s`\n", p);
     COM_DBG("used: %lu\n", used - 0);

     va_start(args, s1);
     while ((s = va_arg(args, char *))) {
	  ldx = strlen(s);
	  if ((ndx += ldx) < ldx || ndx > mdx) break;
	  p = mempcpy(p, (char *)s, ldx);
	  used += ldx;
     }
     va_end(args);
     if (s || mdx != ndx || p != tmp + ndx) {
	  free(tmp);
	  return sz;
     }

     COM_DBG("tmp: `%s'\n", tmp);
     p = mempcpy(dst, tmp, (used > sz ? sz : used));
     free(tmp);
     *p = '\0';
     ++used;

     COM_DBG("dst: `%s'\n", dst);
     COM_DBG("*p: `%c'\n", *p);
     COM_DBG("*--p: `%c'\n", cpeek(p, dst, 0));
     COM_DBG("strlen(dst): %lu\n", strlen(dst));
     COM_DBG("used#2: %lu\n", used - 0);
     com_muntrace;
     return (used > sz ? 0 : sz - used);
}

/* concatm is a little different:
 * unlike `concatl' or `concat', concatm _moves_ memory: that is, the destination
 * pointer can be passed as an argument. */
size_t concatm(char *dst, size_t sz, const char *s1, ...) __attribute__((sentinel));

size_t concatm(char *dst, size_t sz, const char *s1, ...)
{
     va_list args;
     const char *s = NULL;
     char *p, *tmp;
     unsigned long ldx, mdx, ndx;
     size_t used = 0;

     mdx = ndx = strlen(s1);
     va_start(args, s1);
     while ((s = va_arg(args, char *))) {
	  ldx = strlen(s);
	  if ((mdx += ldx) < ldx) break;
     }
     va_end(args);
     if (s || mdx >= INT_MAX) return sz;

     com_mtrace;

# if defined(__cplusplus)
     tmp = (char *)malloc(mdx + 1);
# else
     tmp = malloc(mdx + 1);
# endif
     if (!tmp) return sz;
     bzero(tmp, mdx + 1);

     p = tmp;
     p = mempcpy(p, (char *)s1, ndx);

     used += ndx;
     COM_DBG("p: `%s`\n", p);
     COM_DBG("used: %lu\n", used - 0);

     va_start(args, s1);
     while ((s = va_arg(args, char *))) {
	  ldx = strlen(s);
	  if ((ndx += ldx) < ldx || ndx > mdx) break;
	  p = mempcpy(p, (char *)s, ldx);
	  used += ldx;
     }
     va_end(args);
     if (s || mdx != ndx || p != tmp + ndx) {
	  free(tmp);
	  return sz;
     }
     COM_DBG("tmp: `%s'\n", tmp);
# if defined(mempmove) && COM_USE_MEMPMOVE
     p = mempmove(dst, tmp, (used > sz ? sz : used));
# else
     memmove(dst, tmp, (used > sz ? sz : used));
     p = &dst[(used > sz ? sz : used)];
# endif
     free(tmp);
     *p = '\0';
     ++used;

     COM_DBG("dst: `%s'\n", dst);
     COM_DBG("*p: `%c'\n", *p);
     COM_DBG("*--p: `%c'\n", cpeek(p, dst, 0));
     COM_DBG("strlen(dst): %lu\n", strlen(dst));
     COM_DBG("used#2: %lu\n", used - 0);
     com_muntrace;

     return (used > sz ? 0 : sz - used);
}

# undef catl
# define catl(...) (concatl(__VA_ARGS__, (void *)NULL))

# undef catm
# define catm(...) (concatm(__VA_ARGS__, (void *)NULL))

#endif