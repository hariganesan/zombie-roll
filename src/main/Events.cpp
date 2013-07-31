// Hari Ganesan 7/24/13
// zombie-roll: handling events

#include "Window.hpp"

void MyWindow::handleEvent(SDL_Event e) {
	// MAIN FNS

	if (e.type == SDL_QUIT || 
		 (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q)) {
		isRunning = false;
	} else if (e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) { 
			case SDLK_p: printStatus(); break;
			case SDLK_m: toggleMusic(); break;
			case SDLK_i: //toggleInventory(); break;// TODO: implement method
			default: break;
		}
	}

	// MOVEMENT

	if (e.type == SDL_KEYDOWN) {
		switch(e.key.keysym.sym) {
			case SDLK_a:
			case SDLK_LEFT: keys.left = true; break;
			case SDLK_s:
			case SDLK_DOWN: keys.down = true; break;
			case SDLK_d:
			case SDLK_RIGHT: keys.right = true; break;
			case SDLK_w:
			case SDLK_UP: keys.up = true; break;
			default: break;
		}
	} else if (e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
			case SDLK_a:
			case SDLK_LEFT: keys.left = false; break;
			case SDLK_s:
			case SDLK_DOWN: keys.down = false; break;
			case SDLK_d:
			case SDLK_RIGHT: keys.right = false; break;
			case SDLK_w:
			case SDLK_UP: keys.up = false; break;
			default: break;
		}
	}

	// MOUSE CLICKS

	for (unsigned int i = 0; i < MAX_BUTTON_COUNT; i++) {
		if (buttons[i] && !buttons[i]->isClicked()) {
			buttonsPressed[i] = buttons[i]->handleEvent(e);
		}
	}
}
