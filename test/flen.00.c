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
#include "tub.c"
#include "../src/os.c"

int main()
{
# define flen_00_IDX 0
     size_t lines = 0;
     FILE *lorem_fp = fopen("f/lorem.txt", "r");
     FILE *ipsum_fp = fopen("f/ipsum.txt", "r");
     char *text = malloc(LINE_MAX);
     size_t *known = malloc(sizeof *known);
# include "flen.01.c"
//# include "concat.01.c"
//# include "concat.01.c"
     return EXIT_SUCCESS;
}
