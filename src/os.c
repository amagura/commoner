
/****
  COMMON; os.c, OS/FS related functions

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
#ifndef COMMON_OS_C_GUARD
# define COMMON_OS_C_GUARD 1

# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include "os.h"

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
          return 1;
     } else if (ENOENT == errno) {
          /* `dir' doesn't exist */
          return 0;
     } else {
          return errno;
     }
}

/* returns the number of lines in a file; sets the FILE pointer back to the head
 * of `fp' when done.
 */
size_t flen(FILE *fp)
{
     size_t r;
     while ((EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%*c"))))
          ++r;
     fseek(fp, 0, SEEK_SET);
     return r;
}
#endif
