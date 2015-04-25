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

int intlen(int idx)
{
     int result = 0;
     while (idx) {
	  ++result;
	  idx /= 10;
     }
     return result;
}

int intlenc(const int idx)
{
     int copy = idx;
     int result = 0;
     while (copy) {
	  ++result;
	  copy /= 10;
     }
     return result;
}

size_t intlenm(int src)
{
     size_t dst = 1; /* XXX adds 1 for null-terminator */
     while (src) {
	  ++dst;
	  src /= 10;
     }
     return dst;
}

char cpeek(char *c, char *s, short fwd)
{
     char tmp = '\0';
     if (fwd > 0) {
	  if (c == &s[strlen(s) - 1] || c == &s[strlen(s)])
	       return *c;
	  else
	       tmp = *++c;
	  --c;
     } else if (fwd <= 0) {
	  if (c == s)
	       return *c;
	  else
	       tmp = *--c;
	  ++c;
     }
     return tmp;
}

void rev(char *s)
{
     int hdx[2];
     *hdx = strlen(s) - 1;

     for (int idx = 0; idx < *hdx; ++idx, --hdx[0]) {
	  hdx[1] = s[idx];
	  s[idx] = s[*hdx];
	  s[*hdx] = hdx[1];
     }
}

char *revp(const char *s)
{
     int hdx[2];
     *hdx = strlen(s) - 1;
     char *copy = malloc(*hdx * (sizeof(*copy)) + 1);
     memcpy(copy, s, *hdx + 1);

     for (int idx = 0; idx < *hdx; ++idx, --hdx[0]) {
	  hdx[1] = copy[idx];
	  copy[idx] = copy[*hdx];
	  copy[*hdx] = hdx[1];
     }
     return copy;
}


void repeat(char *dst, const char s, size_t n)
{
     bzero(dst, n);
     char *wp = dst;

     do {
	  *wp = s;
     } while(++wp != &dst[n - 1]);

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
