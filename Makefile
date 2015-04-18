## GNU Makefile


CC ?= clang
_CFLAGS = -std=c99 -O2 -ggdb -g -pipe -Wall -Wextra

SRC = test.c common.c
OBJS = $(SRC:.c=.o)
BIN = test

all: build

build:
	$(CC) $(CFLAGS) $(_CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(BIN) $(SRC)

.c.o:
	$(CC) $(CFLAGS) $(_CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $<

clean:
	$(RM) test || true
	$(RM) *.o || true

valgrind: clean build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN) || true

release: build clean
	git checkout master
	$(RM) Makefile || true
	$(RM) test.c || true
