/****
  COMMON; common.c, (include to include all of common-c)

  Copyright (C) 2015, 2016, 2017, 2018 Alexej G. Magura

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
#if HAVE_CONFIG_H
# include <config.h>
#endif

#if HAVE_STRTONUM
# include <bsd/stdlib.h>
# include <limits.h>
#endif

#include <errno.h>
#include <string.h>
#include "commoner.h"

# if !defined(HAVE_BZERO)
inline void bzero(void *ptr, size_t sz)
{memset(ptr, '\0', sz);}
# endif

# if !defined(HAVE_BCOPY)
inline void bcopy(const void *src, void *dest, size_t n)
{memmove(dest, src, n);}
# endif

# if !defined(HAVE_MEMPCPY)
inline void *mempcpy(void *dest, const void *src, size_t n)
{return memcpy(dest, src, n);}
# endif

inline void *mempmove(void *dest, const void *src, size_t n)
{return memmove(dest, src, n);}

/* if *dst is NULL, remember to free it later */
int stoll(long long *dst, const char *s0)
{
     if (dst == NULL)
	  dst = malloc(1 * sizeof(*dst));

# if HAVE_STRTONUM
     *dst = strtonum(s0, INT_MIN, INT_MAX, NULL);
# else
     *dst = (long long)strtol(s0, NULL, 10);
# endif
     return (errno) ? errno : 0;
}

#if defined(COMMONER_NEEDS_A_MAIN)
int main(int argc, char **argv)
{
     return EXIT_SUCCESS;
}
#endif
