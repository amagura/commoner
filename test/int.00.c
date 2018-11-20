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
     int tmp = rand() % RAND_MAX;
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

     for (int idx = 0; idx < 10; ++idx) {
          n = randm(rand() % RAND_MAX);
          COMNR_DBG("random number: '%d'\n", tmp);
          buf = itoap(tmp);
          base = strlen(buf);
          free(buf);
          ck_assert_int_eq(intlen(tmp), base);
     }
}
END_TEST

START_TEST(test_numlen_accuracy_01)
{
     int n = 40000;
     int len = numlen(n);
     ck_assert_int_eq(len, 5);
}
END_TEST

START_TEST(test_numlen_accuracy_02)
{
     int n = 0;
     int len = 0;
     char *buf = NULL;
     int base = 0;

     for (int idx = 0; idx < 10; ++idx) {
          n = rand() % RAND_MAX;
          COMNR_DBG("random number: '%d'\n", n);
          len = numlen(n);
          base = intlen(n);
          ck_assert_int_eq(len, base);
     }
}
END_TEST
