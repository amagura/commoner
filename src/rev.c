/****
COMMON; rev.c, functions related to reversing strings (should be merged with str.c)

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
#ifndef COMMON_REVERSE_C_GUARD
# define COMMON_REVERSE_C_GUARD 1
# include <stdio.h>
# include <string.h>

void rev(char *s)
{
     int idx = 0;
     int hdx = (int)strlen(s) - 1;

     for (char c; idx < hdx; ++idx, --hdx) {
	  c = s[idx];
	  s[idx] = s[hdx];
	  s[hdx] = c;
     }
}

/* remember to free the returned pointer */
char *revp(const char *s)
{
     int idx = 0;
     int hdx = (int)strlen(s) - 1;
     char *copy = strdup(s);

     for (char c; idx < hdx; ++idx, --hdx) {
	  c = copy[idx];
	  copy[idx] = copy[hdx];
	  copy[hdx] = c;
     }
     return copy;
}

void revn(char *s, size_t n)
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

char *revnp(char *s, size_t n)
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
