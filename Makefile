# Hari Ganesan 2/4/13
# Makefile for zombie-roll

# compiler options
CC=g++
CFLAGS=-pedantic -Wall -I/sw/include
SDL=-L/sw/lib -lSDLmain -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image
COCOA=-framework Cocoa
#GL=-framework OpenGL
SRC=src

all: $(SRC)/*.o zombie clean

# build zombie
zombie: zombie.o Actor.o Battle.o Game.o Render.o Assets.o
	$(CC) -o $@ $(COCOA) $(GL) $(SDL) $^

# build object files
$(SRC)/*.o: $(SRC)/*.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o
