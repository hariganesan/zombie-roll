// Hari Ganesan 2/4/13
// zombie-roll: an rpg

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
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
const char *fontpath = "assets/fonts/chintzy.ttf";

// music
Mix_Music *music = NULL;
const char *musicpath = "assets/music/senomar.mid";

string pngpath = "assets/images/test/1.png";

using namespace std;

void runGame();
void render(Game *g);
GLuint SDL_GL_LoadPNG(string f);
void SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w);
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
	SDL_WM_SetCaption("Zombie Roll", NULL);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
	glClearColor(0, 0, FIELD_COLOR, 1); // RGBA
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
  	//toggleMusic();
  }

  srand(time(NULL));

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
	bool moved = false;
	Keys keys = Keys();

	Game *g = new Game("Your Name Here", D_FIELD);
	g->currentArea = new Area(.1);
	g->png = SDL_GL_LoadPNG(pngpath);

	Battle *b = NULL;

	while (isRunning) {
		// EVENTS
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || 
				 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
				isRunning = false;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
				toggleMusic();
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
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

		if (g->display == D_FIELD) {
			moved = false;
			if (keys.left) {
				if (g->mc->moveLeft()) {
					moved = true;
				}
				keys.left = false;
			} else if (keys.down) {
				if (g->mc->moveDown()) {
					moved = true;
				}
				keys.down = false;
			} else if (keys.right) {
				if (g->mc->moveRight()) {
					moved = true;
				}
				keys.right = false;
			} else if (keys.up) {
				if (g->mc->moveUp()) {
					moved = true;
				}
				keys.up = false;
			}

			// battle!
			if (moved && rand() % 100 < g->currentArea->battlePercent*100) {
				b = g->randomBattle();
				g->display = DT_FIELD_BATTLE;
			}
		} else if (g->display == DT_FIELD_BATTLE) {
			if (g->timer > TT_FIELD_BATTLE) {
				g->timer = 0;
				g->display = D_BATTLE;
				glClearColor(1, 1, 1, 1); //white background
			}
		} else if (g->display == D_BATTLE) {

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
	//SDL_Color TEXT_WHITE = {200, 200, 200};
	//SDL_Color TEXT_BLACK = {20, 20, 20};
	//SDL_Color TEXT_RED = {150, 0, 0};
	//SDL_Rect location;

	////////////////
	// BEGIN DRAWING
	////////////////

	if (g->display == D_FIELD) {
		// draw stuff
		glColor3ub(255, 255, 255);
		glBegin(GL_QUADS);
		glVertex2f(g->mc->x, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y+F_BOX_DIM);
		glVertex2f(g->mc->x, g->mc->y+F_BOX_DIM);
		glEnd();
	} else if (g->display == DT_FIELD_BATTLE) {
		// figure out coordinates
		g->mc->x = g->mc->orig_x + 5*g->timer*cos(g->timer);
		g->mc->y = g->mc->orig_y + 5*g->timer*sin(g->timer);
		g->timer++;

		// draw stuff
		glColor3ub(240, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f(g->mc->x, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y);
		glVertex2f(g->mc->x+F_BOX_DIM, g->mc->y+F_BOX_DIM);
		glVertex2f(g->mc->x, g->mc->y+F_BOX_DIM);
		glEnd();

		// fade to black
		glClearColor(0, 0, FIELD_COLOR - FIELD_COLOR*g->timer/TT_FIELD_BATTLE, 0);

	} else if (g->display == D_BATTLE) {
		SDL_GL_RenderPNG(g->png, 100, 100, 200, 100);
	}

	////////////////
	// END DRAWING
	////////////////

	glPopMatrix();
	SDL_GL_SwapBuffers();
	SDL_Delay(1000/SDL_FRAME_RATE); // frame rate 30ms
	return;
	
}

GLuint SDL_GL_LoadPNG(string f) {
	SDL_Surface *image = IMG_Load(f.c_str());
  if (image == NULL) {
    return -1;
  }
  SDL_DisplayFormatAlpha(image);
  //unsigned object(0);
  GLuint object;
  glGenTextures(1, &object);
  glBindTexture(GL_TEXTURE_2D, object);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
  SDL_FreeSurface(image);

  return object;
}

void SDL_GL_RenderPNG(GLuint object, int x, int y, int h, int w) {
// TODO: transparency and flashing

/*
  int num1 = 300;
  glColor3f(1,0,0);
  glDisable( GL_TEXTURE_2D );
  glBegin( GL_QUADS );
      // Top-left vertex (corner)
      glTexCoord2i( 0, 0 );
      glVertex3f( 0, 0, 0 );

      // Bottom-left vertex (corner)
      glTexCoord2i( 1, 0 );
      glVertex3f( num1, 0, 0 );

      // Bottom-right vertex (corner)
      glTexCoord2i( 1, 1 );
      glVertex3f( num1, num1, 0 );

      // Top-right vertex (corner)
      glTexCoord2i( 0, 1 );
      glVertex3f( 0, num1, 0 );
  glEnd(); */
  glBindTexture( GL_TEXTURE_2D, object );
  glColor3f(1,1,1);
  glEnable( GL_TEXTURE_2D );

  glBegin( GL_QUADS );

      glTexCoord2i( 0, 0 );
      glVertex3f( x, y, 0 );

      glTexCoord2i( 1, 0 );
      glVertex3f( x+w, y, 0 );

      glTexCoord2i( 1, 1 );
      glVertex3f( x+w, y+h, 0 );

      glTexCoord2i( 0, 1 );
      glVertex3f( x, y+h, 0 );
  glEnd();

  SDL_GL_SwapBuffers();

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

