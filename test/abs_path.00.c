
#include "../src/commoner.h"
#include "../src/commoner.c"
#include "../src/os.c"
#include <assert.h>

int main()
{
     char *tmp = abs_path("/home/agm/conf");
     printf("%s: '%s'\n", "tmp", tmp);
     assert(strcmp(tmp, "/home/agm/code/redcomfort") == 0);
     return 0;
}
