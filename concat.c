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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include "common.h"

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

#if defined(__cplusplus)
	result = (char *)malloc(m + 1);
#else
	result = malloc(m + 1);
#endif
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
	return result;
}

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
size_t concatl(char *buf, size_t bufsiz, const char *s1, ...)
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
     if (s || mdx >= INT_MAX) return bufsiz;

#if defined(__cplusplus)
     tmp = (char *)malloc(mdx + 1);
#else
     tmp = malloc(mdx + 1);
#endif
     if (!tmp) return bufsiz;
     bzero(tmp, mdx + 1);
     bzero(buf, mdx + 1);

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
	  return bufsiz;
     }

     *p++ = '\0', ++used;

     COM_DBG("tmp: `%s'\n", tmp);
     COM_DBG("*p: `%c'\n", *(p - 1));
     COM_DBG("*p--: `%c'\n", cpeek(p - 1, tmp, 0));
     COM_DBG("strlen(tmp): %lu\n", strlen(tmp));

#if COM_DLVL > 1
     COM_DBG("used > bufsiz: %d\n", used > bufsiz);
     COM_DBG("used == (strlen(tmp) + 1): %d\n", used == (strlen(tmp) + 1));
     COM_DBG("used#2: %lu\n", used - 0);
     COM_DBG("strlen(tmp)#2: %lu\n", strlen(tmp));
     COM_DBG("mdx + 1: %lu\n", mdx + 1);
     COM_DBG("p == &tmp[%lu + 1]: %d\n", mdx, p == &tmp[mdx + 1]);
     COM_DBG("bufsiz - used: %lu\n", bufsiz - used);
     COM_DBG("used#3: %lu\n", used - 0);
     COM_DBG("p == &tmp[%lu]: %d\n", mdx - 0, p == &tmp[mdx]);
#endif

     memcpy(buf, tmp, (used > bufsiz ? bufsiz : used));
     free(tmp);
     return bufsiz - used;
}
