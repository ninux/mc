# CFLAGS = -pedantic-errors -Wall -Wextra -I. -lm -std=c89
CFLAGS = -I. -lm -std=gnu11 -Wno-variadic-macros

SOURCES = main.c menu.c address.c record.c

nam:
	gcc $(CFLAGS) -o nam.o $(SOURCES)

debug:
	gcc $(CFLAGS) -o debug.o $(SOURCES) -DDEBUG

all:
	gcc $(CFLAGS) -o nam.o $(SOURCES)
	gcc $(CFLAGS) -o debug.o $(SOURCES) -DDEBUG

.PHONY: clean

clean:
	rm nam.o
	rm debug.o
