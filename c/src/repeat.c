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
#include <string.h>
#include "common.h"

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
