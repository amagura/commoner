/****
 Copyright 2015-2019 Alexej Magura

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
#include "tub.c"
#include "../src/int.c"
#include <check.h>
#include <time.h>
#include <unistd.h>

START_TEST(test_intlen_accuracy_01)
{
     /* test using a known number */
     int tmp = 40000;
     ck_assert_int_eq(intlen(tmp), 5);
}
END_TEST

START_TEST(test_intlen_accuracy_02)
{
     /* test using a random number */
     /*int tmp = randm(INT_MAX);*/
     int tmp = rand();
     char *buf = itoap(tmp);
     /*char *base = malloc(sizeof(int)*sizeof(*base));*/
     int base = strlen(buf);
     free(buf);

     ck_assert_int_eq(intlen(tmp), base);
}
END_TEST

START_TEST(test_intlen_accuracy_03)
{
     /*int n = rand() % 10;*/
     int n = 0;
     int tmp = 0;
     char *buf = NULL;
     int base = 0;

     for (int idx = 0; idx < 5; ++idx) {
          n = rand();
          COMNR_DBG("random number: '%d'\n", n);
          buf = itoap(tmp);
          base = strlen(buf);
          free(buf);
          ck_assert_int_eq(intlen(tmp), base);
     }
}
END_TEST

START_TEST(test_randm_randomness)
{
     int base = randm(RAND_MAX);
     int rc = randm(RAND_MAX);
     ck_assert_int_ne(base, rc);
}
END_TEST

START_TEST(test_getrandom_randomness)
{
     uint64_t *base = getrandom();
     uint64_t *rc = getrandom();
     ck_assert_uint_ne(base, (unsigned int)rc);
}
END_TEST
