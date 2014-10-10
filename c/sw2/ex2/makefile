CFLAGS= -pedantic-errors -Wall -I. -lm

main: main.c ninux.c
	gcc $(CFLAGS) -o main.o main.c ninux.c

debug: main.c ninux.c
	gcc $(CFLAGS) -ggdb -o debug.o main.c ninux.c -DDEBUG

all: main.c ninux.c
	gcc $(CFLAGS) -o main.o main.c ninux.c
	gcc $(CFLAGS) -o debug.o main.c ninux.c -DDEBUG

.PHONY: clean

clean:
	rm main.o
	rm debug.o
