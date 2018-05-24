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
#include "../src/commoner.h"
# if !defined(concat_00_IDX)
int main()
{
# else
#  ifndef concat_01_IDX
#   define concat_01_IDX 0
#  elif concat_01_IDX == 0
#   undef concat_01_IDX
#   define concat_01_IDX 1
#  endif
     s = malloc(sz*(sizeof(*s)));
     s0 = malloc(sz0*(sizeof(*s0)));
     strterm(s, sz);
     strterm(s0, sz0);
     getentropy(s0, sz0);
#  if concat_01_IDX == 0
     r = catm(s, sz, s0);
#  elif concat_01_IDX == 1
     r = catl(s, sz, s0);
//#  elif concat_01_IDX == 2
//     r = cat(s, sz, s0);
#  elif concat_01_IDX == 2
     r = concatm(s, sz, s0);
#  elif concat_01_IDX == 3
     r = concatl(s, sz, s0);
#  endif
     printf("r0: %lu\n", (ulong)r);
#  if concat_01_IDX == 0
     r = catm(s, sz, s, s, s);
#  elif concat_01_IDX == 1
     r = catl(s, sz, s, s, s);
//# elif concat_01_IDX == 2
//     r = cat(s, sz, s, s, s);
#  elif concat_01_IDX == 2
     r = concatm(s, sz, s, s, s);
#  elif concat_01_IDX == 3
     r = concatl(s, sz, s, s, s);
#  endif
     printf("r1: %lu\n", (ulong)r);
     r = 0;
     free(s);
     free(s0);
# endif
# if !defined(concat_00_IDX)
     return 0;
}
# endif
