// Hari Ganesan 2/4/13
// zombie-roll: an rpg

#include "Render.hpp"

const char *musicpath = "assets/music/senomar.mid";
const char *pngpath = "assets/images/test/1.png";
const char *fontpath = "assets/fonts/chintzy.ttf";


using namespace std;

void runGame(MyWindow *w);
void toggleMusic(MyWindow *w); // toggles music on and off

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
  MyWindow *w = new MyWindow();

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

	runGame(w);

	Mix_CloseAudio();
	TTF_CloseFont(w->font);
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

void runGame(MyWindow *w) {
	SDL_Event event;

	// game state
	bool isRunning = true;
	bool moved = false;
	Keys keys = Keys();

	Game *g = new Game("Your Name Here", D_FIELD);
	g->currentArea = new Area(.1);
	g->png = w->SDL_GL_LoadPNG(pngpath);

	Battle *b = NULL;

	while (isRunning) {
		// EVENTS
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || 
				 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
				isRunning = false;
			} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
				toggleMusic(w);
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

		w->render(g);
	}
}

void toggleMusic(MyWindow *w) {
	if (w->music == NULL) {
		w->music = Mix_LoadMUS(musicpath);

		// play infinite times
		Mix_PlayMusic(w->music, -1);
	} else {
		Mix_HaltMusic();
		Mix_FreeMusic(w->music);
		w->music = NULL;
	}
}
