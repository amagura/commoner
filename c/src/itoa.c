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
#include "itoa.h"
#include "intlen.h"

void itoa(char *dst, int src)
{
     size_t len = intlenm(src);
     char tmp[len];
     char *wp = tmp;

     for (; src != 0; ++wp, src /= 10) {
	  if (src >= 0)
	       *wp = '0' + (src % 10);
	  else
	       *wp = '0' - (src % 10);
#if COM_DLVL > 1
	  COM_DBG("*wp: `%c`\n", *wp);
#endif
     }
     *wp++ = '\0';
#if COM_DLVL > 1
     COM_DBG("len: %lu\n", len);
     COM_DBG("strlen(tmp): %lu\n", strlen(tmp));
     COM_DBG("sizeof(tmp): %lu\n", sizeof(tmp));
     COM_DBG("tmp: `%s'\n", tmp);
#endif
     rev(tmp);
#if COM_DLVL > 1
     COM_DBG("strlen(tmp)#2: %lu\n", strlen(tmp));
     COM_DBG("sizeof(tmp)#2: %lu\n", sizeof(tmp));
     COM_DBG("tmp#2: `%s'\n", tmp);
#endif
     COM_DBG("tmp#3: `%s'\n", tmp);
     memcpy(dst, tmp, len);
}

char *itoap(const int src)
{
     COM_DBG("src: %d\n", src);
     size_t len = intlenm(src);
     int idx = src;
     char *dst = malloc(len);
     bzero(dst, len);
     char *wp = dst;

     for (; idx != 0; idx /= 10) {
	  if (idx >= 0)
	       *wp++ = '0' + (idx % 10);
	  else
	       *wp++ = '0' - (idx % 10);
     }
     wp = revnp(dst, len);
     *wp = '\0';
     COM_DBG("dst: `%s'\n", dst);

     return dst;
}
