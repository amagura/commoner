/****
  COMMONER; concat.c, (should be merged with similar files)

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
#ifndef COMMONER_CONCAT_C_GUARD
# define COMMONER_CONCAT_C_GUARD 1

# ifdef HAVE_CONFIG_H
#  include <config.h>
# endif

# include "commoner.h"
# if defined(HAVE_BZERO) || defined(HAVE_BCOPY)
#  include <strings.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>

/* XXX OBSOLETE
 *
 */

char *COMMONER_NS(concat)(const char *src, ...) __attribute__((sentinel))
     __attribute__((warn_unused_result))
     __attribute__((deprecated("use concatl or concatm instead")));

// XXX returned value needs free
char *COMMONER_NS(concat)(const char *src, ...)
{
	va_list args;
	const char *src_x;
	char *p, *result;
	unsigned long l, m, n;

	m = n = strlen(src);
	va_start(args, src);

	while ((src_x = va_arg(args, char *))) {
		l = strlen(src_x);
		if ((m += l) < l) break;
	}
	va_end(args);
	if (src_x || m >= INT_MAX) return NULL;
	comnr_mtrace;

# if defined(__cplusplus)
	result = (char *)malloc(m + 1);
# else
	result = malloc(m + 1);
# endif
     if (result == NULL && m + 1 == 0) {
          return NULL;
     }

     p = mempcpy(p = result, src, n);
	va_start(args, src);
	while ((src_x = va_arg(args, char *))) {
		l = strlen(src_x);
		if ((n += l) < l || n > m) break;
		p = mempcpy(p, src_x, l);
	}
	va_end(args);
	if (src_x || m != n || p != result + n) {
		free(result);
		return NULL;
	}
	*p = '\0';
	comnr_muntrace;
	return result;
}

/* unlike `concat', which returns a
 * new pointer that must then be copied
 * or acted upon in some way
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

size_t COMMONER_NS(concatl)(char *dst, size_t dsize, const char *src, ...) __attribute__((sentinel));

size_t COMMONER_NS(concatl)(char *dst, size_t dsize, const char *src, ...)
{
     va_list args;
     const char *src_x = NULL;
     char *p, *tmp;
     unsigned long ldx, mdx, ndx;
     size_t used = 0;

     mdx = ndx = strlen(src);
     va_start(args, src);
     while ((src_x = va_arg(args, char *))) {
	  ldx = strlen(src_x);
	  if ((mdx += ldx) < ldx) break;
     }
     va_end(args);
     if (src_x || mdx >= INT_MAX) return dsize;
     coint_mtrace;
# if defined(__cplusplus)
     tmp = (char *)malloc(mdx + 1);
# else
     tmp = malloc(mdx + 1);
# endif
     if (!tmp) return dsize;
     COMMONER_NS(bzero)(tmp, mdx + 1);
     COMMONER_NS(bzero)(dst, mdx + 1);

     p = tmp;
     p = COMMONER_NS(mempcpy)(p, (char *)src, ndx);

     used += ndx;
     COINT_DBG("p: `%s`\n", p);
     COINT_DBG("used: %lu\n", used - 0);

     va_start(args, src);
     while ((src_x = va_arg(args, char *))) {
	  ldx = strlen(src_x);
	  if ((ndx += ldx) < ldx || ndx > mdx) break;
	  p = COMMONER_NS(mempcpy)(p, (char *)src_x, ldx);
	  used += ldx;
     }
     va_end(args);
     if (src_x || mdx != ndx || p != tmp + ndx) {
	  free(tmp);
	  return dsize;
     }

     COINT_DBG("tmp: `%s'\n", tmp);
     p = COMMONER_NS(mempcpy)(dst, tmp, (used > dsize ? dsize : used));
     free(tmp);
     *p = '\0';
     ++used;

     COINT_DBG("dst: `%s'\n", dst);
     COINT_DBG("*p: `%c'\n", *p);
     COINT_DBG("*--p: `%c'\n", COMMONER_NS(cpeek)(p, dst));
     COINT_DBG("strlen(dst): %lu\n", strlen(dst));
     COINT_DBG("used#2: %lu\n", used - 0);
     coint_muntrace;
     return (used > dsize ? 0 : dsize - used);
}

/* concatm is a little different:
 * unlike `concatl' or `concat', concatm _moves_ memory: that is, the destination
 * pointer can be passed as an argument. */
size_t COMMONER_NS(concatm)(char *dst, size_t dsize, const char *src, ...) __attribute__((sentinel));

size_t COMMONER_NS(concatm)(char *dst, size_t dsize, const char *src, ...)
{
     va_list args;
     const char *src_x = NULL;
     char *p, *tmp;
     unsigned long ldx, mdx, ndx;
     size_t used = 0;

     mdx = ndx = strlen(src);
     va_start(args, src);
     while ((src_x = va_arg(args, char *))) {
	  ldx = strlen(src_x);
	  if ((mdx += ldx) < ldx) break;
     }
     va_end(args);
     if (src_x || mdx >= INT_MAX) return dsize;

     coint_mtrace;

# if defined(__cplusplus)
     tmp = (char *)malloc(mdx + 1);
# else
     tmp = malloc(mdx + 1);
# endif
     if (!tmp) return dsize;
     COMMONER_NS(bzero)(tmp, mdx + 1);

     p = tmp;
     p = COMMONER_NS(mempcpy)(p, (char *)src, ndx);

     used += ndx;
     COINT_DBG("p: `%s`\n", p);
     COINT_DBG("used: %lu\n", used - 0);

     va_start(args, src);
     while ((src_x = va_arg(args, char *))) {
	  ldx = strlen(src_x);
	  if ((ndx += ldx) < ldx || ndx > mdx) break;
	  p = COMMONER_NS(mempcpy)(p, (char *)src_x, ldx);
	  used += ldx;
     }
     va_end(args);
     if (src_x || mdx != ndx || p != tmp + ndx) {
	  free(tmp);
	  return dsize;
     }
     COINT_DBG("tmp: `%s'\n", tmp);
     p = COMMONER_NS(mempmove)(dst, tmp, (used > dsize ? dsize : used));
     free(tmp);
     *p = '\0';
     ++used;

     COINT_DBG("dst: `%s'\n", dst);
     COINT_DBG("*p: `%c'\n", *p);
     COINT_DBG("*--p: `%c'\n", COMMONER_NS(cpeek)(p, dst));
     COINT_DBG("strlen(dst): %lu\n", strlen(dst));
     COINT_DBG("used#2: %lu\n", used - 0);
     coint_muntrace;

     return (used > dsize ? 0 : dsize - used);
}

#if 0
void *COMMONER_NS(shrnkcat)(size_t src_size, size_t max, const char *src, ...) __attribute__((sentinel));

void *COMMONER_NS(shrnkcat)(size_t src_size, size_t max, const char *src, ...)
{
     va_list args;
     const char *src_x = NULL;
     char *p, *tmp;
     p = tmp = NULL;
     unsigned long ldx, mdx, ndx;
     size_t used = 0;

     mdx = ndx = strlen(src);
     va_start(args, src);

     char *buf = malloc(max);
}
#endif
#endif
