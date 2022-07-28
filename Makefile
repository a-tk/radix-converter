CC=gcc
DEBUG=
CFLAGS=-Wall -g $(DEBUG) -lm

.SUFFIXES: .o .c

.c.o: 
	$(CC) $(CFLAGS) -c $<

all: build 


build: converter convrec

converter: converter.o
	$(CC) $(CFLAGS) $< -o $@

convrec: convrec.o
	$(CC) $(CFLAGS) $< -o $@

clean:
	/bin/rm --force *.o converter convrec *.out

