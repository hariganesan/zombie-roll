#ifndef WINDOW_H
#define WINDOW_H

// Hari Ganesan 5/13/13
// zombie-roll: window library file

#include "../Game.hpp"
#include <sstream>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
//#include "SDL/SDL_opengl.h"

using std::stringstream;
const SDL_Color SDL_BLACK = {0, 0, 0};

class Button {
	SDL_Surface *buttonSheet; // sprite sheet
	SDL_Surface *screen; // screen from window
	SDL_Surface *messageOnScreen;
	SDL_Rect box; // attributes of the button

	SDL_Rect clips[4]; // houses each clip
	SDL_Rect *clip;	// part of the sprite sheet

	enum {
		CLIP_MOUSE_OVER,
		CLIP_MOUSE_OUT,
		CLIP_MOUSE_DOWN,
		CLIP_MOUSE_UP
	};

public:
	int timeUntilDisplay;

	Button(SDL_Surface *bs, SDL_Surface *s, int x, int y, int w, int h);
	~Button();
	bool handleEvent(SDL_Event e); // returns true when button was pressed
	void show();
	void click();
	bool isClicked();
};

class MyWindow {
private:
	SDL_Surface *screen; // main window
	SDL_Surface *messageOnScreen; // main message
	SDL_Event event; // log events
	Keys keys; // used with events

	Button *buttons[MAX_BUTTON_COUNT]; // change to vector?
	bool buttonsPressed[MAX_BUTTON_COUNT];

	// game state
	Game *g;
	bool isRunning;
	bool moved;
	TTF_Font *font24;
	Mix_Music *music;
	SDL_Surface *spriteSheets[MAX_SPRITE_SHEET_COUNT];
	SDL_Surface *messages[MAX_MESSAGE_COUNT];

	// init/destroy fns
	void Init();
	void Destroy();
	void initKeys();
	
	// deprecated openGL fns
	//void renderGL();
	//GLuint SDL_GL_LoadPNG(const char *f);
	//void SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w);

	// main loop: events, logic, rendering
	void handleEvent(SDL_Event e);
	void performLogic();
	void renderSDL();

	// dealing with assets
	SDL_Surface *loadImage(string filename);
	void applySurface(int x, int y, SDL_Surface* source, 
										SDL_Surface* destination, SDL_Rect* clip = NULL);
	void toggleMusic();

	// debugging
	void printStatus();

public:
	// fns used by main routine
	MyWindow() : screen(NULL), g(NULL), font24(NULL), music(NULL) { Init(); };
	~MyWindow() { Destroy(); };
	void run();
};

#endif