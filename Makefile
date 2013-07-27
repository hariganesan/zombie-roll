# Hari Ganesan 2/4/13
# Makefile for zombie-roll

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include
SDL=-L/sw/lib -lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image
COCOA=-framework Cocoa
#GL=-framework OpenGL
SRC=src

all: *.o zombie clean

# build zombie
zombie: *.o
	$(CC) -o $@ $(COCOA) $(SDL) $^

# build object files
*.o: $(SRC)/*.cpp $(SRC)/main/*.cpp $(SRC)/ui/*.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
