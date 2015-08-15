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

#ifndef COM_TESTING
# define COM_TESTING 1
#endif

#ifndef COM_DEBUG
# define COM_DEBUG 1
#endif

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/random.h>
#include "../src/concat.c"

int getentropy(void *buf, size_t buflen)
{
     int ret;
     if (buflen > 256)
	  goto failure;
     ret = syscall(SYS_getrandom, buf, buflen, 0);
     if (ret < 0)
	  return ret;
     if (ret == (int)buflen)
	  return 0;
failure:
     errno = EIO;
     return -1;
}

int main()
{
# define concat_00_IDX 0
     const size_t sz = 256*4;
     const size_t sz0 = 256;
     char *s, *s0 = NULL;
     size_t r;
# include "concat.01.c"
# include "concat.01.c"
# include "concat.01.c"
# include "concat.01.c"
     return EXIT_SUCCESS;
}
