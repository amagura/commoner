## Process this file with Automake to generate Makefile.in

#  Copyright 2015 Alexej Magura
#
#  Copying and distribution of this file, with or without modification,
#  are permitted in any medium without royalty provided the copyright
#  notice and this notice are preserved.  This file is offered as-is,
#  without any warranty.

TESTS = check_concat
check_PROGRAMS = check_concat
check_concat_SOURCES = check_concat.c
check_concat_CFLAGS = @CHECK_CFLAGS@
#check_concat_LDADD = $(top_builddir)/src/libconcat.la @CHECK_LIBS@

AM_CFLAGS = -O2

AM_LDFLAGS =

AM_CPPFLAGS =


AM_CFLAGS += -Wall -Wextra

if DEBUG
AM_CFLAGS += -g -ggdb
AM_CPPFLAGS += -DCOM_DEBUG=1
endif

if !DEBUG
if NO_DEBUG
AM_CPPFLAGS += -DCOM_DEBUG=0
endif
endif

if NATIVE
if !GENERIC
AM_CFLAGS += -march=native -mtune=native
endif
endif

if GENERIC
if CPU_KNOWN
AM_CFLAGS += -mtune=generic-$(CPUTYPE)
else
AM_CFLAGS += -mtune=generic
endif
endif

#valgrind: clean test
#	for f in $(bin_PROGRAMS); do \
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./"$$f" ;\
#	done
