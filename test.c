#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int test_catl()
{
     char result[256], input[256];
     repeat(input, 'a', 256);

     int r = (int)catl(result, 256, input);
     COM_DBG("result: `%s'\n", result);
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
     r += (ret == result == (rs - 1));
     idx = rand();
     ret = intlen(idx);
     result = intlenc(idx);
     rs = intlenm(idx);
     r += (ret == result == (rs - 1));
     return r;
}


int main()
{
     int r = 0;
     com_ping;
     r += test_catl();
     com_ping;
     r += test_revs();
     com_ping;
     r += test_itoas();
     com_ping;
     r += test_intlen();
     com_pong;
     return (r == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
