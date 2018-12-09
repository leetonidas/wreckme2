OBJS = $(patsubst %.c,%.o,$(wildcard src/*.c))
CC = gcc
CFLAGS = -fpic -Wall -Wextra -fstack-protector-strong -O3
LDFLAGS = -Wl,-z,now,-z,relro -s

all: wreckme2 test

wreckme2: $(OBJS)
	gcc $(LDFLAGS) -o $@ $^

test: wreckme2
	cat flag.txt | ./wreckme2

clean:
	rm -f $(OBJS) wreckme2

.PHONY: all clean test
