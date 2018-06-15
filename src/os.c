/****
  COMMONER; os.c, OS/FS related functions

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
#ifndef COMMONER_OS_C_GUARD
# define COMMONER_OS_C_GUARD 1

# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>
# include "commoner.h"
# include "os.h"

char *subdir(char **dirs, size_t ssz)
{
     char *src = dirs[0];
     char *dst = dirs[1];
     char *buf = malloc(ssz * sizeof(*buf));
     char *tmp = NULL;
     size_t sz0;

     COINT_DBG("src: '%s'\n", src);
     COINT_DBG("dst: '%s'\n", dst);

     sz0 = catl(buf, ssz, src, dst);
     if (sz0 != ssz && sz0 > 0) {
          tmp = strdup(buf);
          goto rok_free;
     }
     free(buf);
     return NULL;
rok_free:
     free(buf);
     return tmp;

}

char *getdir(int *err, const char *pth)
{
     if (pth == NULL)
          return NULL;

     char *tmp = realpath(pth, NULL);
     /* FIXME: we should check for realpath, and if it is not present,
      * use an alternative
      */

     if (errno) {
          if (err)
               *err = errno;
     }
     return tmp;
}

int rpath(char *pth, size_t n)
{
     if (pth == NULL)
          return -1;

     char *buf = realpath(pth, NULL);
     if (errno) {
          return errno;
     }
     memcpy(pth, buf, n);
     free(buf);
     return 0;
}

/* XXX returns:
 * 1 if true
 * 0 if false
 * errno on error.
 */
bool direxists(char *pth)
{
     DIR *dir = opendir(pth);
     if (dir) {
          /* `dir' exists */
          closedir(dir);
          return true;
     } else if (errno == ENOENT) {
          /* `dir' doesn't exist */
          return false;
     } else {
          return errno;
     }
}

/* returns the number of lines in a file; sets the FILE pointer back to the head
 * of `fp' when done.
 */
size_t flen(FILE *fp)
{
     size_t r = 0;
     /* FIXME: this isn't portable to non-POSIX systems */
     while ((EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%*c"))))
          ++r;
     fseek(fp, 0, SEEK_SET);
     return r;
}

# if 0
/* DO NOT USE */
static int smkstmp(char *tmpfn, const char *templ)
{
     return -1;
}
# endif

# if COINT_INTERNAL_DEBUG
#  pragma GCC push_options
#  pragma GCC optimize ("O0")
# endif
int mkstmp(char *template)
{
     char *tmp, *XXXX;
     uint64_t val;
     int fd, xcnt, cnt, pos,
         tries = pow(62, 3);
     pid_t pid;
     char *wp = strdup(template);
     char *endp = strend(wp);
     size_t len = strlen(wp);
     /* characters used to fill in the X's in template names */
     const char filler[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

     tmp = XXXX = NULL;
     xcnt = cnt = pos = 0;
     pid = getpid();
     srand(time(NULL));
     val = getrandom() * rand() * randm(RAND_MAX) ^ pid;

/* The number of times to attempt to generate a temporary file.
 * POSIX demands that this must be no smaller than TMP_MAX.
 */
# if ((62*62*62) < TMP_MAX)
     tries = TMP_MAX;
# endif

     COINT_DBG("tries: '%d'\n", tries);

     /* find the last X in wp */
     char *sp = strrchr(wp, 'X');
     /* make sure that we at least have one template X */
     if (sp == NULL) {
          /* no period was found in template string */
          errno = EINVAL;
          return -1;
     }
     /* Determine how many X's we have in wp. */
     for (; sp != wp; --sp) {
          if (*sp && *sp == 'X')
               ++xcnt;
          else /* leave loop as soon as we find the first non-X character */
               break;
     }

     /* build substring for strstr */
     COINT_DBG("xcnt: '%d'\n", xcnt);
     char *substr = repeatp('X', xcnt);
     COINT_DBG("substr: '%s'\n", substr);
     COINT_DBG("length of substr: '%d'\n", strlen(substr));

     XXXX = strstr(wp, substr); /* find the head of the suffix in template */

loop:
     /* try to open a unique file that doesn't exist yet until we run out of attempts or succeed. */
     for (int try = 0; try < tries; ++try) {
          /* fill in the X's in template */
          for (cnt = 0; cnt < xcnt; ++cnt) {
               XXXX[cnt] = filler[val % 62]; // 62 is the number of characters in filler
               val /= 62;
               val += randm(RAND_MAX);
          }
          COINT_DBG("wp: '%s'\n", wp);
# if !COINT_INTERNAL_MKSTMP_DRYRUN
          fd = open(wp, O_RDWR | O_CREAT | O_EXCL, 0600);
          if (fd >= 0) {
               memcpy(template, wp, len);
               free(wp);
               free(substr);
               return fd;
          } else if (errno != EEXIST) {
               COINT_DBG("errno: '%d'\n", errno);
               return -2;
          } else if (errno == EEXIST) {
               goto loop;
          }
# endif
     }

     free(wp);
     free(substr);

     /* ran out of tries */
     errno = EAGAIN; // try again
     return -1;
}
# if COINT_INTERNAL_DEBUG
#  pragma GCC pop_options
# endif
#endif
