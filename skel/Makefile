CFLAGS= -pedantic-errors -Wall -I. -lm

main: main.c ninux.c
	gcc $(CFLAGS) -o main.o main.c ninux.c -I.

debug: main.c ninux.c
	gcc $(CFLAGS) -o debug.o main.c ninux.c -I. -DDEBUG

all: main.c ninux.h
	gcc $(CFLAGS) -o main.o main.c ninux.c -I.
	gcc $(CFLAGS) -o debug.o main.c ninux.c -I. -DDEBUG

.PHONY: clean

clean:
	rm main.o
	rm debug.o
