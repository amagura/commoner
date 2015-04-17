## GNU Makefile

_CFLAGS = -std=c99 -O2 -ggdb -g -pipe -Wall -Wextra

SRC = bin/test.c
OBJS = $(SRC:.c=.o)
BIN = $(OBJS:.o=)

all: $(BIN)

.c.o:
	$(CC) $(CFLAGS) $(_CFLAGS) ($CPPFLAGS) $(LDFLAGS) -o $@ $<

clean:
	$(RM) bin/test.o
	$(RM) bin/test
	$(RM)

test: $(BIN)
