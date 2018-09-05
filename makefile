
CC=gcc
CFLAGS=-I
DEPS = mp3.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -g -c mp3.c 

mp3: mp3.o
	$(CC) -g -o mp3 mp3.o

