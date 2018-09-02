
CC=gcc
CFLAGS=-I.
DEPS = Assignment1a.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Assignment1a: Assignment1a.o
	$(CC) -o Assignment1a Assignment1a.o

