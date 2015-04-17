#include <stdio.h>
#include <stdlib.h>
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


int main()
{
     int r = 0;
//     r += test_catl();
     r += test_revs();
     return (r == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

