/****
 Copyright 2015-2018 Alexej Magura

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
#include <stdlib.h>
# if !defined(flen_00_IDX)
int main()
{
# else
#  ifndef c_01_IDX
#   define flen_01_IDX 0
#  elif flen_01_IDX == 0
#   undef flen_01_IDX
#   define flen_01_IDX 1
#  endif
     // get known-good number of lines
     /*fscanf(known, "%*[^\n]", ipsum_fp);*/
     fread(text, 1, 2, ipsum_fp);
     sscanf(text, "%zu", known);
     comnr_log("number of lines in lorem_fp is known to be: '%zu'", known);
     fclose(ipsum_fp);
     lines = flen(lorem_fp);
     /*asm("nop");*/
     COMNR_NOP();

#  if flen_01_IDX == 0
     /*r = catm(s, sz, s0);*/
#  elif flen_01_IDX == 1
     /*r = catl(s, sz, s0);*/
//#  elif flen_01_IDX == 2
//     r = cat(s, sz, s0);
#  elif flen_01_IDX == 2
     /*r = flenm(s, sz, s0);*/
#  elif flen_01_IDX == 3
     /*r = flenl(s, sz, s0);*/
#  endif
     /*printf("r0: %lu\n", (ulong)r);*/
#  if flen_01_IDX == 0
     /*r = catm(s, sz, s, s, s);*/
#  elif flen_01_IDX == 1
     /*r = catl(s, sz, s, s, s);*/
//# elif flen_01_IDX == 2
//     r = cat(s, sz, s, s, s);
#  elif flen_01_IDX == 2
     /*r = flenm(s, sz, s, s, s);*/
#  elif flen_01_IDX == 3
     /*r = flenl(s, sz, s, s, s);*/
#  endif
     /*printf("r1: %lu\n", (ulong)r);*/
     /*r = 0;*/
     /*free(s);*/
     /*free(s0);*/
# endif
# if !defined(flen_00_IDX)
     return 0;
}
# endif
