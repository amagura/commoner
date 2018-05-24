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

#define COM_TESTING 1
#define COM_DEBUG 1
#include "../src/commoner.h"

int test_catl()
{
     char result[256], input[256];
     repeat(input, 'a', 256);

     int r = (int)catl(result, 256, input);
     COM_DBG("result: `%s'\n", result);

     bzero(result, 256);
     bzero(input, 256);
     repeat(input, 'b', 129);
     catm(result, 256, input);
     r += (int)catm(result, 256, result, input);
     COM_DBG("r: %d\n", r);
     COM_DBG("result#2: `%s'\n", result);
     return r;
}

int test_revs()
{
     int r = 0;
     char *wp;
     char s[6] = "hello";

     const char tmp[8] = "goodbye";

     rev(s);
     r = (s[0] == 'o' ? 0 : 1);
     wp = revp(tmp);
     r = (wp[0] == 'e' ? 0 : 1);
     r = (tmp[0] == 'g' ? 0 : 1);
     free(wp);
     return r;
}

int test_itoas()
{
     int r = 0;
     int idx = 12345;
     char *s = itoap(idx);
     COM_DBG("s: `%s'\n", s);
     r += strcmp(s, "12345");
     free(s);
     s = malloc(intlenm(987654));
     itoa(s, 987654);
     r += strcmp(s, "987654");
     free(s);
     return r;
}

int test_intlen()
{
     int r, ret, result;
     size_t rs = 0;
     r = 0;
     int idx = 256;
     ret = intlen(idx);
     result = intlenc(idx);
     rs = intlenm(idx);
     COM_DBG("ret: %d, result: %d, rs: %lu\n", ret, result, (unsigned long)rs);
     r += ret - result;
     COM_DBG("r: %d\n", r);
     r += ret - (int)(rs - 1);
     COM_DBG("ret - (rs - 1): %d\n", ret - (int)(rs - 1));
     COM_DBG("r#2: %d\n", r);
     return r;
}

int test_repeats()
{
     int r = 0;
     char *dst = strprep("hello", 3);
     size_t n = (sizeof("hello") - 1) * 3 + 1;
     r += strcmp("hellohellohello", dst);
     COM_DBG("r: %d\n", r);
     r += !(strlen("hellohellohello") == strlen(dst));
     COM_DBG("r: %d\n", r);
     free(dst);
     dst = malloc(n);
     strrep(dst, "hello", n);
     COM_DBG("dst: `%s'\n", dst);
     free(dst);
     return r;
}

int test_strcdelim()
{
     int r = 0, c[2], *idx;
     char s[] = "\"hello\"";
     char s1[] = "{hello}{";
     idx = strndelim(s, '"', '"', c);

     if (idx) {
	  COM_DBG("idx[0]: %d\n", c[0]);
	  COM_DBG("idx[1]: %d\n", c[1]);
	  r += c[0] - c[1];
     } else {
	  r += 1;
     }

     idx = strndelim(s1, '{', '}', c);
     if (idx) {
	  COM_DBG("c[0]: %d\n", c[0]);
	  COM_DBG("c[1]: %d\n", c[1]);
	  r += c[0] - c[1] - 1;
     } else {
	  r += 1;
     }
     return r;
}

int test_strwodq()
{
     int r = 0;
     char *s = "\"hello\"";
     size_t n = sizeof("\"hello\"");
     char *s1 = malloc(n);

     r += strwodq(s1, s, n);
     COM_DBG("s1: `%s'\n", s1);
     free(s1);

     s1 = strwodqp(s);
     r += strcmp(s1, "hello");
     COM_DBG("s1#2: `%s'\n", s1);
     free(s1);

     return r;
}

int main()
{
     int r = 0;
     com_neko("r: %d\n", r);
     r += test_catl();
     com_neko("r: %d\n", r);
     r += test_revs();
     com_neko("r: %d\n", r);
     r += test_itoas();
     com_neko("r: %d\n", r);
     r += test_intlen();
     com_neko("r: %d\n", r);
     r += test_repeats();
     com_neko("r: %d\n", r);
     r += test_strcdelim();
     com_neko("r: %d\n", r);
     r += test_strwodq();
     return (r == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
