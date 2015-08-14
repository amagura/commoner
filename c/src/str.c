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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpeek.c"
#include "concat.c"
#include "common.h"

int *strndelim(const char *s, const char od, const char cd, int count[2])
{
     memset(count, 0, sizeof(*count)*2);
     char *c = strchr(s, '\0');

     if (c == s)
	  return NULL;

     do {
	  if (c != s && cpeek(c, s, 0) == '\\')
	       continue;
	  if (*c == cd)
	       ++count[1];
	  else if (*c == od)
	       ++count[0];
     } while (c-- != s);

     if (od == cd && count[1] > 0) {
	  if (count[1] % 2 == 1)
	       while (count[0]++ < --count[1]);
	  else {
	       count[0] = count[1] * 0.5;
	       count[1] *= 0.5;
	  }
     }

     return count;
}

char *strwodqp(const char *src)
{
     size_t n = strlen(src) + 1;
     int c[2] = {0, 0}, even = 0;
     char *tmp, *token, *rest, *newp;
     tmp = token = rest = newp = NULL;

     if (!strndelim(src, '"', '"', c))
	  return NULL;

     if (c[0] == 0)
	  return NULL;

     tmp = strdup(src);
     newp = malloc(n);
     even = c[0] - abs(c[0] - c[1]);

     token = strtok_r(tmp, "\"", &rest);

     if (token == NULL) {
	  free(newp);
	  return NULL;
     }

     catl(newp, n, token);
     while ((token = strtok_r(NULL, "\"", &rest)) != NULL) {
	  if (even % 2 == 1) {
	       catm(newp, n, newp, token);
	       --even;
	  } else {
	       ++even;
	  }
     }

     free(tmp);
     return newp;
}

int strwodq(char *dst, const char *src, size_t n)
{
     int c[2] = {0, 0};
     int even = 0;
     int r = 0;
     char *tmp = NULL;
     char *token = NULL;
     char *rest = NULL;
     char *newp = NULL;

     if (!strndelim(src, '"', '"', c)) {
	  r += 1;
	  goto end;
     }

     if (c[0] == 0) {
	  r += 2;
	  goto end;
     }

     tmp = strdup(src);
     newp = malloc(n);
     even = c[0] - abs(c[0] - c[1]);

     token = strtok_r(tmp, "\"", &rest);
     if (token == NULL) {
	  r += 3;
	  goto free;
     }
     catl(newp, n, token);

     while ((token = strtok_r(NULL, "\"", &rest)) != NULL) {
	  if (even % 2 == 1) {
	       catm(newp, n, newp, token);
	       --even;
	  } else {
	       ++even;
	  }
     }

     memcpy(dst, newp, n);

free:
     free(tmp);
     free(newp);
end:
     return r;
}
