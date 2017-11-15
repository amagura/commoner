/****
COMMON; repeat.c, (should be merged with str.c)

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
#ifndef COMMON_REPEAT_C_GUARD
# define COMMON_REPEAT_C_GUARD 1
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "common.h"

void repeat(char *dst, const char s, size_t n)
{
     bzero(dst, n);
     char *wp = dst;

     do {
	  *wp = s;
     } while (++wp != &dst[n - 1]);

     dst[n] = '\0';
     COM_DBG("dst: `%s'\n", dst);
     COM_DBG("strlen(dst): %lu\n", strlen(dst));
     COM_DBG("sizeof(dst): %lu\n", sizeof(dst));
     COM_DBG("sizeof(void *): %lu\n", sizeof(void *));
}

int strrep(char *dst, const char *s, size_t n)
{
     bzero(dst, n);
     char *wp = dst;
     int r = 0;

     size_t ssiz = strlen(s), tsiz;
     tsiz = ssiz;

     if (ssiz > n-1)
	  goto end;
     tsiz += ssiz;

     do {
	  wp = mempcpy(wp, (char *)s, ssiz);
     } while (tsiz += ssiz, tsiz < n-1);

     *wp++ = '\0';
end:
     return r;
}

char *strprep(const char *s, int times)
{
     size_t ssiz = strlen(s);
     char *copy = malloc(ssiz * times + 1);
     char *wp = copy;

     for (; times > 0; --times)
	  wp = mempcpy(wp, (char *)s, ssiz);

     *wp++ = '\0';
     return copy;
}
#endif
