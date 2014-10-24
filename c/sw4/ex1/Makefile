CFLAGS = -pedantic-errors -Wall -I. -lm
SOURCES = main.c stack.c

main:
	gcc $(CFLAGS) -o main.o $(SOURCES)

debug:
	gcc $(CFLAGS) -o debug.o $(SOURCES) -DDEBUG

all:
	gcc $(CFLAGS) -o main.o $(SOURCES)
	gcc $(CFLAGS) -o debug.o $(SOURCES) -DDEBUG

.PHONY: clean

clean:
	rm main.o
	rm debug.o
