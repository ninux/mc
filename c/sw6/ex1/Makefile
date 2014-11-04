# CFLAGS = -pedantic-errors -Wall -Wextra -I. -lm -std=c89
CFLAGS = -I. -lm -std=gnu11 -Wno-variadic-macros
OBJECT_PATH = obj/

SOURCES = main.c menu.c address.c record.c

nam:
	gcc $(CFLAGS) -o $(OBJECT_PATH)nam.o $(SOURCES)

debug:
	gcc $(CFLAGS) -o $(OBJECT_PATH)debug.o $(SOURCES) -DDEBUG

all:
	gcc $(CFLAGS) -o $(OBJECT_PATH)nam.o $(SOURCES)
	gcc $(CFLAGS) -o $(OBJECT_PATH)debug.o $(SOURCES) -DDEBUG

.PHONY: clean

clean:
	rm $(OBJECT_PATH)nam.o
	rm $(OBJECT_PATH)debug.o
