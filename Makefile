# Hari Ganesan 2/4/13
# Makefile for zombie-roll

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include -L/sw/lib
SDL=-lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image
COCOA=-framework Cocoa
GL=-framework OpenGL -L/sw/lib
SRC=src

all: $(SRC)/*.o zombie clean

# build zombie
zombie: zombie.o Actor.o Battle.o Render.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

# build object files
$(SRC)/*.o: $(SRC)/*.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
