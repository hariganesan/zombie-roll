// Hari Ganesan 7/24/13
// zombie-roll: handling events

#include "Window.hpp"

void MyWindow::handleEvent(SDL_Event e) {
	if (event.type == SDL_QUIT || 
		 (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_q)) {
		isRunning = false;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_p) {
		printStatus();
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_m) {
		toggleMusic();
	} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
		keys.left = true;
	} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
		keys.down = true;
	} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
		keys.right = true;
	} else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
		keys.up = true;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
		keys.left = false;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
		keys.down = false;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
		keys.right = false;
	} else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
		keys.up = false;
	}
}
