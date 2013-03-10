# Hari Ganesan 2/4/13
# Makefile for zombie-roll

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include -L/sw/lib
SDL=-lSDLmain -lSDL -lSDL_ttf -lSDL_mixer
COCOA=-framework Cocoa
GL=-framework OpenGL -L/sw/lib
SRC=src

all: zombie clean

# build zombie
zombie: zombie.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

zombie.o: $(SRC)/*.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
