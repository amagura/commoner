/****
COMMON; mem.c, memory related functions (should probably be merged with str.c)

Copyright (C) 2015, 2016, 2017 Alexej G. Magura

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
****/
#ifndef COMMON_MEM_C_GUARD
# define COMMON_MEM_C_GUARD 1

# include <string.h>
# include "common.h"

int memlen(const char *s)
{
     char *a = NULL;
     if ((a = strchr(s, '\0')))
	  return (int)(a - s);
     return -1;
}

char *strterm(char *s, size_t sz)
{
     char *tmp = NULL;
     tmp = s;
     s += sz;
     --s; --s;
     *s = '\0';
     s = tmp;
     return s;
}
#endif
