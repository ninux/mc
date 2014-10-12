CFLAGS = -pedantic-errors -Wall -I. -lm
SOURCES = main.c list.c

main: $(SOURCES)
	gcc $(CFLAGS) -o main.o $(SOURCES) -I.

debug: $(SOURCES)
	gcc $(CFLAGS) -o debug.o $(SOURCES) -I. -DDEBUG

all: $(SOURCES)
	gcc $(CFLAGS) -o main.o $(SOURCES) -I.
	gcc $(CFLAGS) -o debug.o $(SOURCES) -I. -DDEBUG

.PHONY: clean

clean:
	rm *.o
