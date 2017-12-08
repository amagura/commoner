/****
  COMMON; common.c, (include to include all of common-c)

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
#if HAVE_CONFIG_H
# include <config.h>
#endif

#include "str.c"
#include "int.c"
#include "os.c"
#include "commoner.h"


#if defined(COMMON_NEEDS_A_MAIN)
int main()
{
     return EXIT_SUCCESS;
}
#endif
