/****
  COMMON; msg.c, Message/Output related functions

  Copyright (C) 2015, 2016, 2017, 2018 Alexej G. Magura

  This file is a part of Commoner

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
#ifndef COMMONER_MSG_C_GUARD
# define COMMONER_MSG_C_GUARD 1

# include <stdarg.h>
# include <string.h>

# if HAVE_CONFIG_H
#  include <config.h>
# endif

# include "commoner.h"

void die(int *rc, const char *format, ...) __attribute__((sentinel));
void die(int *rc, const char *format, ...)
{
     va_list lap;
     va_start(lap, format);
     vprintf(format, lap);
     va_end(lap);
     exit(rc == NULL ? EXIT_FAILURE : *rc);
}

void kys(const char *format, ...) __attribute__((sentinel));
void kys(const char *format, ...)
{
     va_list lap;
     va_start(lap, format);
     vprintf(format, lap);
     va_end(lap);
     exit(EXIT_FAILURE);
}

void croak(int *rc, const char *msg, ...) __attribute__((sentinel));
void croak(int *rc, const char *msg, ...)
{
     const char *s0;
     printf("%s: %s\n", PROGNAME, msg);

     va_list args;
     va_start(args, msg);
     while ((s0 = va_arg(args, const char *))) {
          printf("%s\n", s0);
     }
     va_end(args);
     exit(rc == NULL ? EXIT_FAILURE : *rc);
}

void ribbt(const char *msg, ...) __attribute__((sentinel));
void ribbt(const char *msg, ...)
{
     const char *s0;
     printf("%s: %s\n", PROGNAME, msg);
     va_list args;
     va_start(args, msg);
     while ((s0 = va_arg(args, const char *))) {
          printf("%s\n", s0);
     }
     va_end(args);
     printf("Try `%s' --help' for more information\n", PROGNAME);
     exit(EXIT_FAILURE);
}


#endif /* COMMONER_MSG_C_GUARD */
