// Hari Ganesan 5/13/13
// zombie-roll: render library file

#include "Game.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
//#include "SDL/SDL_opengl.h"

class MyWindow {
private:
	SDL_Surface *screen; // main window
	SDL_Event event; // log events
	Keys keys; // used with events

	// game state
	Game *g;
	bool isRunning;
	bool moved;
	TTF_Font *font12;
	Mix_Music *music;
	SDL_Surface *spriteSheets[MAX_SPRITE_SHEET_COUNT];

	// init/destroy fns
	void Init();
	void Destroy();
	void initKeys();
	
	// deprecated openGL fns
	//void renderGL();
	//GLuint SDL_GL_LoadPNG(const char *f);
	//void SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w);
	void renderSDL();
	
	// dealing with assets
	SDL_Surface *loadImage(string filename);
	void applySurface(int x, int y, SDL_Surface* source, 
										SDL_Surface* destination, SDL_Rect* clip = NULL);
	void toggleMusic();

	// testing
	void pushDots();

	// debugging
	void printStatus();

public:
	// fns used by main routine
	MyWindow() : screen(NULL), g(NULL), font12(NULL), music(NULL) { Init(); };
	~MyWindow() { Destroy(); };
	void run();
};