CFLAGS = -I. -lm -std=gnu11 -Wno-variadic-macros

SOURCES = main.c

main:
	gcc $(CFLAGS) -o main.o $(SOURCES)

debug:
	gcc $(CFLAGS) -g -o debug.o $(SOURCES) -DDEBUG

all:
	gcc $(CFLAGS) -o main.o $(SOURCES)
	gcc $(CFLAGS) -g -o debug.o $(SOURCES) -DDEBUG

.PHONY: clean

clean:
	rm main.o
	rm debug.o
