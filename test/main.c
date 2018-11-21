#include <check.h>
#include "int.00.c"
#include "../src/commoner.h"
#include "../src/commoner.c"

Suite * int_suite()
{
     Suite *s;
     TCase *tc_core;

     s = suite_create("Int");

     tc_core = tcase_create("Core");

     /* intlen */
     tcase_add_test(tc_core, test_intlen_accuracy_01);
     tcase_add_test(tc_core, test_intlen_accuracy_02);
     tcase_add_test(tc_core, test_intlen_accuracy_03);

     /* numlen */
     /*tcase_add_test(tc_core, test_numlen_accuracy_01);*/
     /*tcase_add_test(tc_core, test_numlen_accuracy_02);*/

     /* randm */
     tcase_add_test(tc_core, test_randm_randomness);
     suite_add_tcase(s, tc_core);

     return s;
}


int main()
{
     rseed();
     int number_failed;
     Suite *s;
     SRunner *sr;

     s = int_suite();
     sr = srunner_create(s);

     srunner_run_all(sr, CK_VERBOSE);
     number_failed = srunner_ntests_failed(sr);
     srunner_free(sr);
     return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

