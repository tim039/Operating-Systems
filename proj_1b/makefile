

CC=gcc
CFLAGS=-I
DEPS=mycp.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -g -c mycp.c

mycp: mycp.o
	$(CC) -g -o mycp mycp.o


