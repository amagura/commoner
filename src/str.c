/****
  COMMON; str.c, String related functions

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
#ifndef COMMON_STRING_C_GUARD
# define COMMON_STRING_C_GUARD 1

# if HAVE_CONFIG_H
#  include <config.h>
# endif

# include "commoner.h"
# include <stdio.h>
# include <stdlib.h>
# if !defined(_POSIX_C_SOURCE)
#  define _POSIX_C_SOURCE 200809L /* for strdup */
# endif
# include <string.h>
# include <stdarg.h>
# include <ctype.h>

# if !defined(errno)
#  include <errno.h>
# endif

# if COMMONER_VERSION == 0x100
#  include <concat.c>
#  include <repeat.c>
#  include <rev.c>
# endif

# if !defined(CHAR_MAX)
#  include <limits.h>
# endif

# if 0
# define COMNR_BM_ALPHABET_LEN CHAR_MAX

// bad character table
void COMMONER_NS(pbm_bad)(char *str, uint8_t *pat, int32_t patlen)
{
     int idx;
     void a()
     {
     };

     int32_t *NOT_FOUND = &patlen;

     /* initialize pat */
     for (idx = 0; idx < COMNR_BM_ALPHABET_LEN; ++idx)
          pat[idx] = *NOT_FOUND;
     for (idx = 0; idx < patlen - 1; ++idx)
          pat[str[idx]] = patlen - idx - 1;
}


char *COMMONER_NS(boyer_moore)(char *str, size_t ssz, char *pat, size_t patsz)
{

     if (patsz == 0)
          return str;

     /*int sdec, jdx;*/
     /*sdec = jdx = 0;*/

     /*char shift[patsz];*/
     /*char bpos[patsz];*/
     for

     /* NOTE: patsz should include space for the NULL byte */

     for
     /*COMMONER_NS(bzero)(&shift, patsz);*/



/*uint8_t COMMONER_NS(boyer_moore)(char *text, size_t tsize, char *pat, size_t psize)*/
/*{*/
     /*int idx;*/
     /*// bad character shift*/
     /*char *badc[CHAR_MAX];*/
     /*// good suffix shift*/
     /*char *goods[CHAR_MAX];*/

     /*for (idx = 0; idx < CHAR_MAX; ++idx) {*/
          /*text[*/


     /*static void boyer_moore_pre(char *text, char **/
# endif
# if 0
void COMMONER_NS(ceaser)(char *s, const int x)
{
     char *wp = s;
     const char *alpha[2] = {"abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

     for (; *wp; ++wp) {
          if (!isalpha(*wp))
               continue;

          // get end of alpha[0] (lowend cannot be changed in any way)
          const char * const lowend = COMMONER_NS(strend)(alpha[0]);
          // get end of alpha[1]
          const char * const upend = COMMONER_NS(strend)(alpha[1]);

          const char * const end = isupper(*wp) ? upend : lowend;
          int idx = (end == upend) ? 1 : 0;
          const char * const head = &alpha[idx][0];

          // wp is Z
          if (wp == end) {
               *wp = alpha[idx][x - 1]; // minus 1 for taking Z to A
               // wp is not Z, but x takes it beyond Z
          } else if ((*wp + x) > *end) {
               int diff = *wp + x;
               int ntmp = diff - *end;
               *wp = alpha[idx][x - ntmp];
          } else {
               // deals with negative numbers
               int z = x >= 0 ? x : x % 26;
               if (z < 0) {
                    int diff = *wp + x;
                    if (diff < 'A') {
                         diff -= 'A';
                         diff = abs(diff);
                    }

                    goto next;
               }
               int low = tolower(*wp) - 'a' + z;
               *wp = alpha[idx][low % 26];
          }
next:
          0;

     }
}
# endif

char *COMMONER_NS(rmchar)(const char *src, const char c, size_t *n)
{
     const char *wp = src;
     size_t len = 0;

     if (n == NULL)
          len = strlen(src) + 1;
     else
          len = *n;

     char *dst = malloc(len);

     if (dst == NULL && len != 0) {
          comnr_errno = errno;
          return NULL;
     }

     bzero(dst, len);

     for (; *wp; ++wp)
          if (*wp != c)
               *dst = *wp;

     *dst = '\0';
     return dst;
}

int COMMONER_NS(chars)(const char *s, const char c)
{
     int cnt = 0;
     const char *wp = s;
     for (; *wp; ++wp)
          if (*wp == c)
               ++cnt;
     return cnt;
}

int COMMONER_NS(charstermp)(const char *s, const char c, const char *endp)
{
     int cnt = 0;
     const char *wp = s;
     if (endp) {
          for (; *wp && wp > endp; ++wp) {
               if (*wp == c)
                    ++cnt;
          }
     } else {
          for (; *wp && wp < endp; --wp) {
               if (*wp == c)
                    ++cnt;
          }
     }
     return cnt;
}

int COMMONER_NS(charsterm)(const char *s, const char c, const char head, const char end)
{
     int cnt = 0;
     const char *wp = s;
     for (; *wp && *wp != head; ++wp); // go to start of range
     for (; *wp && *wp != end; ++wp) {
          if (*wp == c)
               ++cnt;
     }
     return cnt;
}

void COMMONER_NS(trim)(char *str)
{
     char *wp = NULL;
     size_t len = strlen(str);
     for (wp = str + len; isspace(*wp); --wp); /* shrink wp to not include trailing spaces */
     wp[1] = '\0';
     for (wp = str; isspace(*wp); ++wp); /* shrink wp to not include leading spaces */
     memmove(str, wp, len - (size_t)(wp - str) + 1);
}

char *COMMONER_NS(ptrim)(const char *str)
{
     if (!str)
          return NULL;

     char *wp = strdup(str);

     if (wp == NULL) {
          comnr_errno = errno;
          return NULL;
     }

     size_t len = strlen(str);
     char *tmp = wp + len;
     for (; isspace(*tmp); --tmp);
     tmp[1] = '\0';
     for (tmp = wp; isspace(*tmp); ++tmp);
     memmove(wp, tmp, len - (size_t)(tmp - wp) + 1);
     return wp;
}

int COMMONER_NS(cmpstrs)(const char *base, size_t n, ...) __attribute__((sentinel));
int COMMONER_NS(cmpstrs)(const char *base, size_t n, ...)
{
     const char *pmatch; /* potential match */
     va_list args;
     va_start(args, n);
     int idx = 0; /* position within va_args where the match occurs */
     int missed = 0; /* number of positions that didn't match */

     while ((pmatch = va_arg(args, const char *))) {
          ++idx;
          if (strncasecmp(base, pmatch, n) == 0)
               break;
          else
               ++missed;
     }
     va_end(args);

     if (missed == idx)
          return -1;
     else
          return idx;
}

int COMMONER_NS(cmpcase)(const char *base, size_t n, ...) __attribute__((sentinel));
int COMMONER_NS(cmpcase)(const char *base, size_t n, ...)
{
     const char *pmatch;
     va_list args;
     va_start(args, n);
     int idx = 0;
     int missed = 0;

     /* using a do-while loop here only makes sense if we call va_arg before it */
     while ((pmatch = va_arg(args, const char *))) {
          ++idx;
          if (strncmp(base, pmatch, n) == 0)
               break;
          else
               ++missed;
     }
     va_end(args);

     if (missed == idx)
          return -1;
     else
          return idx;
}

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
char *COMMONER_NS(strend)(const char *s0)
{
# if defined(_GNU_SOURCE)
     char *endp = strchr(s0, '\0') - 1;
# else
     char *endp = (char *)&s0[strlen(s0)];// - 1;
# endif
     /* FIXME: this shouldn't return NULL for both when s0 is NULL and when *s0
      * is '\0'.
      */
     if (s0 != NULL && *s0 != '\0')
          return (s0 == endp ? (char *)s0 : endp);
     return s0 == NULL ? NULL : (char *)s0;
}

# if defined(COM_EXPOSE_OLD_CPEEK)
char COMMONER_NS(old_cpeek)(const char *c, const char *s, const short fwd)
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
char COMMONER_NS(cpeek)(const char *const sp0, const char *const head)
{
     if (!head) // FIXME this is less than ideal usage of strend...
          return (*sp0 == '\0' || sp0 == strend(sp0) ? *sp0 : *(sp0 + 1));
     else
          return (sp0 == head) ? *sp0 : *(sp0 - 1);
}

int *COMMONER_NS(strndelim)(const char *s0, const char od, const char cd, int count[2])
{
     bzero(count, sizeof(*count)*2); // times 2 because count is an array of two.
     /*memset(count, 0, sizeof(*count)*2);*/
     char *c = strend(s0);

     if (c == s0) // we are looking at the end of the string
          goto fail;

     do {
          /* FIXME: this was recently changed from the old cpeek
           * to the newer cpeek, but it has __not__ been tested!!
           */
          if (c != s0 && COMMONER_NS(cpeek)(c, s0) == '\\')
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

char *COMMONER_NS(strwodqp)(const char *src)
{
     size_t n = strlen(src) + 1;
     int c[2] = {0, 0}, even = 0;
     char *tmp, *token, *rest, *newp;
     tmp = token = rest = newp = NULL;

     if (!COMMONER_NS(strndelim)(src, '"', '"', c))
          return NULL;

     if (c[0] == 0)
          return NULL;

     tmp = strdup(src);

     if (tmp == NULL) {
          comnr_errno = errno;
          return NULL;
     }

     newp = malloc(n);

     if (newp == NULL && n != 0) {
          free(tmp);
          comnr_errno = errno;
          return NULL;
     }

     even = c[0] - abs(c[0] - c[1]);

     token = strtok_r(tmp, "\"", &rest);

     if (token == NULL) {
          free(newp);
          comnr_errno = 0;
          return NULL;
     }

     COMMONER_NS(catl)(newp, n, token);
     while ((token = strtok_r(NULL, "\"", &rest)) != NULL) {
          if (even % 2 == 1) {
               COMMONER_NS(concatm)(newp, n, newp, token, (void *)NULL);
               --even;
          } else {
               ++even;
          }
     }

     free(tmp);
     return newp;
}

int COMMONER_NS(strwodq)(char *dst, const char *src, size_t n)
{
     int c[2] = {0, 0};
     int even = 0;
     int r = 0;
     char *tmp = NULL;
     char *token = NULL;
     char *rest = NULL;
     char *newp = NULL;

     if (!COMMONER_NS(strndelim)(src, '"', '"', c)) {
          r += 1;
          goto end;
     }

     if (c[0] == 0) {
          r += 2;
          goto end;
     }

     tmp = strdup(src);

     if (tmp == NULL) {
          comnr_errno = errno;
          r += 1;
          goto end;
     }

     newp = malloc(n);

     if (newp == NULL && n != 0) {
          free(tmp);
          comnr_errno = errno;
          r += 1;
          goto end;
     }

     even = c[0] - abs(c[0] - c[1]);

     token = strtok_r(tmp, "\"", &rest);
     if (token == NULL) {
          r += 3;
          goto free;
     }

     COMMONER_NS(concatl)(newp, n, token, (void *)NULL);

     while ((token = strtok_r(NULL, "\"", &rest)) != NULL) {
          if (even % 2 == 1) {
               COMMONER_NS(concatm)(newp, n, newp, token, (void *)NULL);
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

/////////////////////////////////////////
// Taken from defunct mem.c
/////////////////////////////////////////
int COMMONER_NS(memlen)(const char *s)
{
     char *a = NULL;
     if ((a = strchr(s, '\0')))
	  return (int)(a - s);
     return -1;
}

char *COMMONER_NS(strterm)(char *s, size_t sz)
{
     char *tmp = NULL;
     tmp = s;
     s += sz;
     --s; --s;
     *s = '\0';
     s = tmp;
     return s;
}

void *COMMONER_NS(memdup)(const void *src, size_t n)
{
     void *tmp = malloc(n);
     memcpy(tmp, src, n);
     return tmp;
}
/////////////////////////////////////////
// End of defunct mem.c
/////////////////////////////////////////

/////////////////////////////////////////
// Taken from defunct repeat.c
/////////////////////////////////////////
/* XXX Remember to pass n+1 to repeat:
 * If you want 7 d's and you pass 7 as *n*,
 * you'll only get 6: the 7th character will be
 * the NULL terminator--*n* is the size of the destination;
 * not how many characters you want.
 */
int COMMONER_NS(repeat)(char *dst, const char c, size_t n)
{
     if (n == 0) {
          dst = NULL;
          return 1;
     }

     COMMONER_NS(bzero)(dst, n);
     char *wp = dst;

     do {
          *wp = c;
     } while (++wp != &dst[n - 1]);

     dst[n] = '\0';
     COINT_DBG("dst: `%s'\n", dst);
     COINT_DBG("strlen(dst): %lu\n", strlen(dst));
     COINT_DBG("sizeof(dst): %lu\n", sizeof(dst));
     COINT_DBG("sizeof(void *): %lu\n", sizeof(void *));
     return 0;
}

/* XXX *n* is how many characters you want */
char *COMMONER_NS(repeatp)(const char c, int n)
{
     if (n == 0)
          return NULL;
     char *wp = malloc(n + 1);
     COINT_DBG("n + 1: '%d'\n", n + 1);
     char *headp = wp;
     COMMONER_NS(bzero)(wp, n + 1);
     do {
          *wp = c;
     } while (++wp != headp + n);

     wp[n + 1] = '\0';
     return headp;
}

int COMMONER_NS(strrep)(char *dst, const char *s, size_t n)
{
     COMMONER_NS(bzero)(dst, n);
     char *wp = dst;
     int r = 0;

     size_t ssiz = strlen(s), tsiz;
     tsiz = ssiz;

     if (ssiz > n-1)
          goto end;
     tsiz += ssiz;

     do {
          wp = COMMONER_NS(mempcpy)(wp, (char *)s, ssiz);
     } while (tsiz += ssiz, tsiz < n-1);

     *wp++ = '\0';
end:
     return r;
}

char *COMMONER_NS(strprep)(const char *s, int times)
{
     size_t ssiz = strlen(s);
     char *copy = malloc(ssiz * times + 1);
     char *wp = copy;

     for (; times > 0; --times)
          wp = COMMONER_NS(mempcpy)(wp, (char *)s, ssiz);

     *wp++ = '\0';
     return copy;
}
/////////////////////////////////////////
// End of defunct repeat.c
/////////////////////////////////////////

/////////////////////////////////////////
// Taken from defunct rev.c
/////////////////////////////////////////
void COMMONER_NS(rev)(char *s)
{
     int idx = 0;
     int hdx = (int)strlen(s);

     for (char c; idx < hdx; ++idx, --hdx) {
	  c = s[idx];
	  s[idx] = s[hdx];
	  s[hdx] = c;
     }
}

/* remember to free the returned pointer */
char *COMMONER_NS(revp)(const char *s)
{
     int idx = 0;
     int hdx = (int)strlen(s);
     char *copy = strdup(s);

     for (char c; idx < hdx; ++idx, --hdx) {
	  c = copy[idx];
	  copy[idx] = copy[hdx];
	  copy[hdx] = c;
     }
     return copy;
}

void COMMONER_NS(revn)(char *s, size_t n)
{
     --n;
     if (strchr(s, '\0'))
	  --n;
     int idx = 0;
     for (char tmp; idx < (int)n; ++idx, --n) {
	  tmp = s[idx];
	  s[idx] = s[n];
	  s[n] = tmp;
     }
}

char *COMMONER_NS(revnp)(char *s, size_t n)
{
     const size_t len = --n;
     if (strchr(s, '\0'))
	  --n;
     int idx = 0;
     for (char tmp; idx < (int)n; ++idx, --n) {
	  tmp = s[idx];
	  s[idx] = s[n];
	  s[n] = tmp;
     }
     return &s[0] + len;
}
#endif
