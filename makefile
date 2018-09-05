
CC=gcc
CFLAGS=-I
DEPS = Assignment1a.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -g -c Assignment1a.c 

Assignment1a: Assignment1a.o
	$(CC) -g -o Assignment1a Assignment1a.o

