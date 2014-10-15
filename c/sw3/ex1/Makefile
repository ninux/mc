CC = gcc
CFLAGS = -pedantic-errors -Wall -I. -lm -std=c99 -g -ggdb
OBJ = main.o list.o
APPL = main.exe

.PHONY: all
all : main.exe

$(APPL) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(APPL)

%.obj : %.c Makefile
	$(CC) $(CFLAGS) –c $(.SOURCE)
