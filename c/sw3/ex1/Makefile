CFLAGS = -pedantic-errors -Wall -I. -lm -std=c99
SOURCES = main.c list.c

.PHONY: all
all : all_internal

main: $(SOURCES)
	gcc $(CFLAGS) -o main.o $(SOURCES) -I.

debug: $(SOURCES)
	gcc $(CFLAGS) -o debug.o $(SOURCES) -I. -DDEBUG

all_internal: $(SOURCES)
	gcc $(CFLAGS) -o main.o $(SOURCES) -I.
	gcc $(CFLAGS) -o debug.o $(SOURCES) -I. -DDEBUG


.PHONY: clean
clean:
	rm -f *.o
