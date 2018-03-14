/****
  COMMON; str.c, String related functions

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
#ifndef COMMON_STRING_C_GUARD
# define COMMON_STRING_C_GUARD 1
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <ctype.h>

# if COMMONER_VERSION == 0x100
#  include <concat.c>
#  include <repeat.c>
#  include <rev.c>
# endif

# include "commoner.h"

// I just don't see the point in having an `atend' function.  Testing for the
// end of a string is quite simple.
# if 0
bool atend(const char *s)
{
     return (strend(s) == NULL
# endif
/* does not change the contents of s0 or change
 * the memory location that s0 points to.
 *
 * returns the end of s0 (not the null terminator)
 *
 * XXX returns NULL if s0 is NULL
 * and returns s0 as-is if s0 points to '\0'
 *
 * compare the return value to s0: if they are the same
 * then s0 pointed to '\0'
 */
char *strend(const char *s0)
{
# if defined(_GNU_SOURCE)
     char *endp = strchr(s0, '\0') - 1;
# else
     char *endp = (char *)&s0[strlen(s0)] - 1;
# endif
     /* FIXME: this shouldn't return NULL for both when s0 is NULL and when *s0
      * is '\0'.
      */
     if (s0 != NULL && *s0 != '\0')
          return (s0 == endp ? (char *)s0 : endp);
     return s0 == NULL ? NULL : (char *)s0;
}

# if defined(COM_EXPOSE_OLD_CPEEK)
char old_cpeek(const char *c, const char *s, const short fwd)
{
     if (fwd > 0) {
	  if (*c == '\0'
# if defined(_GNU_SOURCE)
	      || c == strchr(s, '\0') - 1
# else
	      || c == &s[strlen(s)]
# endif
	       )
	       return *c;
	  else
	       return *(c + 1);
     }
     return (c == s) ? *c : *(c - 1);
}
# endif

/* if head is NULL, then we look backwards */
char cpeek(const char *const sp0, const char *const head)
{
     if (!head) // FIXME this is less than ideal usage of strend...
          return (*sp0 == '\0' || sp0 == strend(sp0) ? *sp0 : *(sp0 + 1));
     else
          return (sp0 == head) ? *sp0 : *(sp0 - 1);
}

int *strndelim(const char *s0, const char od, const char cd, int count[2])
{
     memset(count, 0, sizeof(*count)*2);
# if defined(_GNU_SOURCE)
     char *c = strchr(s0, '\0');
# else
     char *c = (char *)&s0[strlen(s0)];
# endif
     if (c == s0) // we are looking at the end of the string
          goto fail;

     do {
          /* FIXME: this was recently changed from the old cpeek
           * to the newer cpeek, but it has __not__ been tested!!
           */
          if (c != s0 && cpeek(c, s0) == '\\')
               continue;
          if (*c == cd)
               ++count[1];
          else if (*c == od)
               ++count[0];
     } while (c-- != s0);

     if (od == cd && count[1] > 0) {
          if (count[1] % 2 == 1)
               while (count[0]++ < --count[1]);
          else {
               count[0] = count[1] * 0.5;
               count[1] *= 0.5;
          }
     }
     return count;
fail:
     return NULL;
}

char *strwodqp(const char *src)
{
     size_t n = strlen(src) + 1;
     int c[2] = {0, 0}, even = 0;
     char *tmp, *token, *rest, *newp;
     tmp = token = rest = newp = NULL;

     if (!strndelim(src, '"', '"', c))
          return NULL;

     if (c[0] == 0)
          return NULL;

     tmp = strdup(src);
     newp = malloc(n);
     even = c[0] - abs(c[0] - c[1]);

     token = strtok_r(tmp, "\"", &rest);

     if (token == NULL) {
          free(newp);
          return NULL;
     }

     catl(newp, n, token);
     while ((token = strtok_r(NULL, "\"", &rest)) != NULL) {
          if (even % 2 == 1) {
               catm(newp, n, newp, token);
               --even;
          } else {
               ++even;
          }
     }

     free(tmp);
     return newp;
}

int strwodq(char *dst, const char *src, size_t n)
{
     int c[2] = {0, 0};
     int even = 0;
     int r = 0;
     char *tmp = NULL;
     char *token = NULL;
     char *rest = NULL;
     char *newp = NULL;

     if (!strndelim(src, '"', '"', c)) {
          r += 1;
          goto end;
     }

     if (c[0] == 0) {
          r += 2;
          goto end;
     }

     tmp = strdup(src);
     newp = malloc(n);
     even = c[0] - abs(c[0] - c[1]);

     token = strtok_r(tmp, "\"", &rest);
     if (token == NULL) {
          r += 3;
          goto free;
     }
     catl(newp, n, token);

     while ((token = strtok_r(NULL, "\"", &rest)) != NULL) {
          if (even % 2 == 1) {
               catm(newp, n, newp, token);
               --even;
          } else {
               ++even;
          }
     }

     memcpy(dst, newp, n);

free:
     free(tmp);
     free(newp);
end:
     return r;
}

void trim(char *s0)
{
     char *wp = NULL;
     size_t len = strlen(s0);
     for (wp = s0 + len - 1; isspace(*wp); --wp); /* shrink wp to not include trailing spaces */
     wp[1] = '\0';
     for (wp = s0; isspace(*wp); ++wp); /* shrink wp to not include leading spaces */
     memmove(s0, wp, len - (size_t)(wp - s0) + 1);
}

char *ptrim(const char *s0)
{
     char *wp = strdup(s0);
     size_t len = strlen(s0);
     char *tmp = wp + len - 1;
     for (; isspace(*tmp); --tmp);
     tmp[1] = '\0';
     for (tmp = wp; isspace(*tmp); ++tmp);
     memmove(wp, tmp, len - (size_t)(tmp - wp) + 1);
     return wp;
}

# if 0
int cmpstrs(int res, bool _case, const char *rc, ...) __attribute__((sentinel));
int cmpstrs(int res, bool _case, const char *rc, ...)
{
     const char *base;
     va_list args;
     va_start(args, rc);
     int idx = 1; // position of match in function call
     while ((s0 = va_arg(args, const char *))) {
          if (_case)
               if ((strncasecmp(rc, base, res)) == 0) {
               }
          else
               if ((
# endif

/////////////////////////////////////////
// Taken from defunct mem.c
/////////////////////////////////////////
int memlen(const char *s)
{
     char *a = NULL;
     if ((a = strchr(s, '\0')))
	  return (int)(a - s);
     return -1;
}

char *strterm(char *s, size_t sz)
{
     char *tmp = NULL;
     tmp = s;
     s += sz;
     --s; --s;
     *s = '\0';
     s = tmp;
     return s;
}

void *memdup(const void *src, size_t n)
{
     void *tmp = malloc(n);
     memcpy(tmp, src, n);
     return tmp;
}
#endif
