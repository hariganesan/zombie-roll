// Hari Ganesan 2/4/13
// zombie-roll: an rpg

#include "Render.hpp"

//const char *musicpath = "assets/music/senomar.mid";
//const char *pngpath = "assets/images/test/";
//const char *fontpath = "assets/fonts/chintzy.ttf";

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
    std::cerr << "Unable to open audio!" << std::endl;
    exit(1);
  } else {
  	//toggleMusic();
  }

  srand(time(NULL));

  // open and close window
  MyWindow *w = new MyWindow();
  w->run();
	delete w;

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}
