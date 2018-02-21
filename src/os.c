/****
  COMMONER; os.c, OS/FS related functions

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
#ifndef COMMONER_OS_C_GUARD
# define COMMONER_OS_C_GUARD 1

# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
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

char *abs_path(const char *pth)
{
     if (pth == NULL) return NULL; /* no path given */
     /* FIXME: we should check for realpath, and if it is not present,
      * use an alternative
      */
     char *buf = realpath(pth, NULL);
     if (errno)
          return NULL;
     return buf;
}

/* On success: *pth is set to the realpath to *pth and 0 is returned.
   On failure: *pth is set to NULL and either errno or -1 is returned.
   */

int rpath(char *pth)
{
     if (pth == NULL) return -1;
     /* FIXME: we should check for realpath, and if it is not present,
      * use an alternative
      */
     char *buf = malloc(PATH_MAX + 1);
     realpath(pth, buf);
     if (errno) {
          pth = NULL;
          return errno;
     }
     memmove(pth, buf, sizeof(PATH_MAX + 1)); // NOTE may cause mem leaks?
     free(buf);
     return 0;
}

/* XXX returns:
 * 1 if true
 * 0 if false
 * errno on error.
 */
int direxists(char *pth)
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
     while ((EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%*c"))))
          ++r;
     fseek(fp, 0, SEEK_SET);
     return r;
}
#endif
