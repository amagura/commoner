#include <stdio.h>
#include "../common.h"

int test_catl()
{
     char input[256];
     int r;
     r = (int)catl(input, 256, repeat("a", 256));
     return r;
}

int main()
{
     int r;
     r = test_catl();
     return (r == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
