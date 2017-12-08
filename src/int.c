/****
  COMMONER; int.c, integer related functions

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
#ifndef COMMONER_INT_C_GUARD
# define COMMONER_INT_C_GUARD 1
# include <stdint.h>
# include "commoner.h"

uintmax_t uintm_len(uintmax_t idx)
{
	uintmax_t r = 0;
	while (idx) {
		++r;
		idx /= 10;
	}
	return r;
}

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

/////////////////////////////////////////
// Taken from defunct itoa.c
/////////////////////////////////////////
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
# if COMNR_INTERNAL_DLVL > 1
	  COMNR_DBG("*wp: `%c`\n", *wp);
# endif
     }
     *wp++ = '\0';
# if COMNR_INTERNAL_DLVL > 1
     COMNR_DBG("len: %lu\n", len);
     COMNR_DBG("strlen(tmp): %lu\n", strlen(tmp));
     COMNR_DBG("sizeof(tmp): %lu\n", sizeof(tmp));
     COMNR_DBG("tmp: `%s'\n", tmp);
# endif
     rev(tmp);
# if COMNR_INTERNAL_DLVL > 1
     COMNR_DBG("strlen(tmp)#2: %lu\n", strlen(tmp));
     COMNR_DBG("sizeof(tmp)#2: %lu\n", sizeof(tmp));
     COMNR_DBG("tmp#2: `%s'\n", tmp);
# endif
     COMNR_DBG("tmp#3: `%s'\n", tmp);
     memcpy(dst, tmp, len);
}

char *itoap(const int src)
{
     COMNR_DBG("src: %d\n", src);
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
     COMNR_DBG("dst: `%s'\n", dst);

     return dst;
}
#endif
