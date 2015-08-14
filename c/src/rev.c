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
