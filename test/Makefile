#  Copyright 2015-2019 Alexej Magura
#
#  Copying and distribution of this file, with or without modification,
#  are permitted in any medium without royalty provided the copyright
#  notice and this notice are preserved.  This file is offered as-is,
#  without any warranty.

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mydir := $(abspath $(lastword $(dir $(MAKEFILE_LIST))))
cwd := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

CFLAGS ?= -std=c11 -O0 -Wall -Wextra -D_GNU_SOURCE -g -ggdb -DCOM_DEBUG=1 -DCOM_TESTING=1
LDFLAGS ?=
LDFLAGS += -lcheck -lcommoner
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

BLKLIST = tub.c
SRCS = $(filter-out $(BLKLIST),$(wildcard *.c))
OBJS = $(SRCS:.c=.o)
TESTS = $(OBJS:.o=)

all: ext $(TESTS)

expand:
	$(CC) $(CFLAGS) $(CPPFLAGS) -E $(SRCS)

ext: $(OBJS)

check: $(TESTS)
	$(foreach p,$(TESTS),cat /dev/null > "$(p:=.mog)"; mtrace MALLOC_TRACE="$(p:=.mog)" ./"$(p)" | tee -a "$(p:=.mog)";)

clean:
	$(foreach f,$(TESTS),$(RM) "$(f)" "$(f:=.o)"; )
	$(foreach wc,*.vog *.mog,test -z "$(wildcard $(wc))" || $(RM) $(wildcard $(wc)); )

qclean:
	@$(foreach f,$(TESTS),$(RM) "$(f)" "$(f:=.o)"; )
	@$(foreach wc,*.vog *.mog,test -z "$(wildcard $(wc))" || $(RM) $(wildcard $(wc)); )


valgrind: $(TESTS)
	$(foreach t,$(TESTS),valgrind $(VFLAGS) ./"$(t)" &> "$(t:=.vog)"; printf "\033[31mexited: $$?\033[0m\n" >> "$(t:=.vog)"; )


#run: $(TESTS)
#	$(foreach p,$(TESTS),
