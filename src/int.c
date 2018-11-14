/****
  COMMONER; int.c, integer related functions

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
#ifndef COMMONER_INT_C_GUARD
# define COMMONER_INT_C_GUARD 1

# if HAVE_CONFIG_H
#  include <config.h>
# endif

# include "commoner.h"
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <sys/time.h>

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
/* XXX The `randm' function is licensed under the terms of the Creative Commons License, said terms can be found here:
 * https://creativecommons.org/licenses/by-sa/3.0/
 *
 * Please see NOTICE file for authorship details.
 */

/* assumes 0 <= max <= RAND_MAX */
long randm(long max) {
     /* max <= RAND_MAX < ULONG_MAX, so this is okay */
     unsigned long nbin = (unsigned long) max + 1,
                   nrand = (unsigned long) RAND_MAX + 1,
                   binsz = nrand / nbin,
                   defect = nrand % nbin;
     long x0;
     do {
          x0 = random();
     } // this is carefully written not to overflow
     while (nrand - defect <= (unsigned long)x0);
     // truncated division is intentional
     return x0/binsz;
}

/* returns, hopefully, a bunch of random bits based on the current timestamp */
uint64_t getrandom()
{
     struct timeval tv;
     gettimeofday(&tv, NULL);
     uint64_t bits = ((uint64_t) tv.tv_usec << 16) ^ tv.tv_sec;
     return bits;
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
# if COINT_INTERNAL_DLVL > 1
	  COINT_DBG("*wp: `%c`\n", *wp);
# endif
     }
     *wp++ = '\0';
# if COINT_INTERNAL_DLVL > 1
     COINT_DBG("len: %lu\n", len);
     COINT_DBG("strlen(tmp): %lu\n", strlen(tmp));
     COINT_DBG("sizeof(tmp): %lu\n", sizeof(tmp));
     COINT_DBG("tmp: `%s'\n", tmp);
# endif
     rev(tmp);
# if COINT_INTERNAL_DLVL > 1
     COINT_DBG("strlen(tmp)#2: %lu\n", strlen(tmp));
     COINT_DBG("sizeof(tmp)#2: %lu\n", sizeof(tmp));
     COINT_DBG("tmp#2: `%s'\n", tmp);
# endif
     COINT_DBG("tmp#3: `%s'\n", tmp);
     memcpy(dst, tmp, len);
}

char *itoap(const int src)
{
     COINT_DBG("src: %d\n", src);
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
     COINT_DBG("dst: `%s'\n", dst);

     return dst;
}
#endif
