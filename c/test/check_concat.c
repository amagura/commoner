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
#include <check.h>

#if !defined(COM_TESTING)
# define COM_TESTING 1
#endif

#if !defined(COM_DEBUG)
# define COM_DEBUG 1
#endif

#include "../src/mac.h"

#include "../src/concat.c"
#include "../src/repeat.c"

#if defined(_GNU_SOURCE)
# include <mcheck.h>
# define com_mtrace	\
     do {		\
	  mtrace();	\
     } while(0)
# define com_muntrace	\
     do {		\
	  muntrace();	\
     } while(0)
#else
# define com_mtrace
# define com_muntrace
#endif



START_TEST (test_catm_return)
{

     char s0[512];
     size_t r = 0;
     com_mtrace;
     repeat(s0, 'b', 256);
     com_muntrace;
     r = catm(s0, 512, s0, s0);
     ck_assert_int_eq((int)r, 0);
}
END_TEST

START_TEST (test_catm_malloc)
{
     com_mtrace;
     char *s1 = malloc(768*(sizeof(*s1)));
     size_t r = 0;
     repeat(s1, 'c', 768);
     r = catm(s1, 384, s1, s1);
     ck_assert_int_eq((int)r, 384);
     free(s1);
     com_muntrace;
}
END_TEST

Suite * concatm_suite()
{
     Suite *catm_s = suite_create("Concatm");
     TCase *tc_core = tcase_create("Core");
     tcase_add_test(tc_core, test_catm_return);
     tcase_add_test(tc_core, test_catm_malloc);
     suite_add_tcase(catm_s, tc_core);

     return catm_s;
}

int main()
{
     int failed = 0;
     SRunner *sr = srunner_create(concatm_suite());

     srunner_run_all(sr, CK_NORMAL);
     failed = srunner_ntests_failed(sr);
     srunner_free(sr);
     return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
