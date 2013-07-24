// Hari Ganesan 2/4/13
// zombie-roll: an rpg

#include "Window.hpp"

//const char *musicpath = "assets/music/senomar.mid";
//const char *pngpath = "assets/images/test/";
//const char *fontpath = "assets/fonts/chintzy.ttf";

int main(int argc, char **argv) {
	// initialize sdl and ttf
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return EXIT_FAILURE;

	if (TTF_Init() == -1)
		return EXIT_FAILURE;

	if (Mix_OpenAudio(AUDIO_RATE, AUDIO_S16, 
										AUDIO_CHANNELS, AUDIO_BUFFERS) == -1) {
		return EXIT_FAILURE;
	}

	// deprecated openGL fns
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//glClearColor(0, 0, FIELD_COLOR, 1); // RGBA
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);// viewable part of the window
	//glShadeModel(GL_SMOOTH); // add a gradient
	//glMatrixMode(GL_PROJECTION); // 2D drawing
	//glLoadIdentity(); // save state
	//glDisable(GL_DEPTH_TEST); // disable 3D drawing

	// open and close window
	MyWindow *w = new MyWindow();
	w->run();
	delete w;

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}
