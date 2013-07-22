// Hari Ganesan 5/13/13
// zombie-roll: render library file

#include "Game.hpp"

class MyWindow {
private:
	SDL_Event event;

	// game state
	Game *g;
	bool isRunning;
	bool moved;

	// font
	TTF_Font *font;
	// music
	Mix_Music *music;
	//keys
	Keys keys;

	void Init();
	void Destroy();
	void initKeys();
	void render();
	GLuint SDL_GL_LoadPNG(const char *f);
	void SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w);
	void toggleMusic();
	void printStatus();

public:
	MyWindow() : font(NULL), music(NULL) { Init(); };
	~MyWindow() { Destroy(); };
	void run();
};