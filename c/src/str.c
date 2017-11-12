/****
COMMON; str.c, String related functions

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
#ifndef COMMON_STRING_C_GUARD
# define COMMON_STRING_C_GUARD 1
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "repeat.c"
# include "cpeek.c"
# include "rev.c"
# include "concat.c"
# include "mem.c"
# include "common.h"

inline int char *getend(const char *s)
{
# if defined(_GNU_SOURCE)
	return strchr(s, '\0');
# else
	return &s[strlen(s)];
}

inline bool atend(const char *s)
{
# if defined(_GNU_SOURCE)
	return (strchr(s, '\0') == s ? true : false);
# else
	return (&s[strlen(s)] == s ? true : false);
# endif
}

int *strndelim(const char *s, const char od, const char cd, int count[2])
{
     memset(count, 0, sizeof(*count)*2);
# if defined(_GNU_SOURCE)
     char *c = strchr(s, '\0');
# else
     char *c = &s[strlen(s)];
# endif
     if (c == s)
	  return NULL;

     do {
	  if (c != s && cpeek(c, s, 0) == '\\')
	       continue;
	  if (*c == cd)
	       ++count[1];
	  else if (*c == od)
	       ++count[0];
     } while (c-- != s);

     if (od == cd && count[1] > 0) {
	  if (count[1] % 2 == 1)
	       while (count[0]++ < --count[1]);
	  else {
	       count[0] = count[1] * 0.5;
	       count[1] *= 0.5;
	  }
     }

     return count;
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
#endif
