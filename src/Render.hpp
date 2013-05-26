// Hari Ganesan 5/13/13
// zombie-roll: render library file

#include "Battle.hpp"

class MyWindow {

public:
	// font
	TTF_Font *font;
	// music
	Mix_Music *music;
	// images

	MyWindow() : font(NULL), music(NULL) {};
	void render(Game *g);
	GLuint SDL_GL_LoadPNG(string f);
	void SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w);
};