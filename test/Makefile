# Hari Ganesan 2/4/13
# Makefile for zombie-roll testing

# compiler options
CC=g++
CFLAGS=-pedantic -Wall

all: test clean

test: test.o
	$(CC) -o $@ $^

clean:
	rm *.o
