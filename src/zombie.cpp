// Hari Ganesan 2/4/13
// zombie-roll: an rpg

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"
#include <iostream>
#include <string>

#include "Battle.hpp"

// window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MARGIN = 10;

// font
TTF_Font *font;
const char *fontpath = "fonts/chintzy.ttf";

// music
Mix_Music *music = NULL;
const char *musicpath = "music/senomar.mid";

// display options
enum {
	D_HOME,
	D_FIELD,
	D_BATTLE
};

using namespace std;

void runGame();
void render(Game *g);
void SDL_GL_RenderText(const char *text, SDL_Color color, SDL_Rect *location);
void toggleMusic(); // toggles music on and off

int main(int argc, char **argv) {
	// initialize sdl, ttf, and opengl
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// initialize window properties
	SDL_WM_SetCaption("Magic Hat", NULL);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
	glClearColor(0, 0, 0.3, 1); // RGBA
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); // viewable part of the window
	glShadeModel(GL_SMOOTH); // add a gradient
	glMatrixMode(GL_PROJECTION); // 2D drawing
	glLoadIdentity(); // save state
	glDisable(GL_DEPTH_TEST); // disable 3D drawing

	//initialize audio properties
	int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16;
  int audio_channels = 2;
  int audio_buffers = 4096;
  
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  } else {
  	toggleMusic();
  }

	runGame();

	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void runGame() {
	SDL_Event event;

	// game state
	bool isRunning = true;
	Keys keys = Keys();

	int display = D_FIELD;
	Game *g = new Game();

	while (isRunning) {
		// EVENTS
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || 
				 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
				isRunning = false;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
				toggleMusic();
			}


			if        (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
				keys.left = true;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
				keys.down = true;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
				keys.right = true;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
				keys.up = true;
			}
		}

		// LOGIC

		if (display == D_FIELD) {
			if        (keys.left) {
				g->mc->moveLeft();
				keys.left = false;
			} else if (keys.down) {
				g->mc->moveDown();
				keys.down = false;
			} else if (keys.right) {
				g->mc->moveRight();
				keys.right = false;
			} else if (keys.up) {
				g->mc->moveUp();
				keys.up = false;
			}
		}

		// RENDERING

		render(g);
	}
}

void render(Game *g) {
		glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	// TODO: change to 0,1 for depth
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1); // set matrix
	SDL_Color TEXT_WHITE = {200, 200, 200};
	SDL_Color TEXT_BLACK = {20, 20, 20};
	SDL_Color TEXT_RED = {150, 0, 0};
	SDL_Rect location;

	////////////////
	// BEGIN DRAWING
	////////////////

	glColor3ub(255, 255, 255);
	// draw stuff
	glBegin(GL_QUADS);
	glVertex2f(g->mc->x, g->mc->y);
	glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y);
	glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y+F_BOX_DIM);
	glVertex2f(g->mc->x, g->mc->y+F_BOX_DIM);
	glEnd();


	////////////////
	// END DRAWING
	////////////////

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(33); // frame rate 30ms
	return;
	
}

void toggleMusic() {
	if (music == NULL) {
		music = Mix_LoadMUS(musicpath);

		// play infinite times
		Mix_PlayMusic(music, -1);
	} else {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}
}

