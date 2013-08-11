// Hari Ganesan 7/22/13
// zombie-roll: loading and rendering assets

#include "Window.hpp"

SDL_Surface *MyWindow::loadImage(string filename) {
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	if (!(loadedImage = IMG_Load(filename.c_str()))) {
		cerr << "unable to load image " << filename << endl;
		return NULL;
	}

	if (!(optimizedImage = SDL_DisplayFormat(loadedImage))) {
		cerr << "unable to optimize image " << filename << endl;
		SDL_FreeSurface(loadedImage);
		return NULL;
	}

	SDL_FreeSurface(loadedImage); // free old surface
	// set color key
	SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, 
									SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));

	return optimizedImage;
}

void MyWindow::applySurface(int x, int y, SDL_Surface* source, 
														SDL_Surface* destination, SDL_Rect* clip) {
	SDL_Rect offset; // holds offsets

	// get offsets
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset); // blit surface
}

void MyWindow::renderSDL() {
	// draw background
	if (g->display == DT_FIELD_BATTLE && g->timer % FLASH_RATE*2 >= FLASH_RATE) {
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	} else {
		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	}

	// FIELD

	if (g->display == D_FIELD) {

		// DRAW MC

		Vec2d mcPos = g->mc->getPosition();
		unsigned int sprite = g->mc->getSprite();
		SDL_Rect clip;
		clip.x = (sprite % g->mc->getSpriteColCount())*100; // fIX
		clip.y = sprite/g->mc->getSpriteRowCount()*100;
		clip.w = SPRITE_WIDTH;
		clip.h = SPRITE_HEIGHT;

		// get spritesheet 0 and attach MC to screen
		applySurface(mcPos.x, mcPos.y, spriteSheets[0], screen, &clip);

	// BATTLE

	} else if (g->display == D_BATTLE) {

		// SBAR
		// TODO: edit constants for screen positions

		stringstream hpText;
		int i = 0;
		for (vector<PartyMember>::const_iterator iter = g->party.begin();
				 iter != g->party.end(); iter++, i++) {
			hpText.clear();
			hpText.str("");
			hpText << iter->getID() << " ";
			hpText << iter->getRemainingHP() << "/" << iter->getTotalHP();
			SDL_Surface *hpSurface = TTF_RenderText_Solid(font24,
																										hpText.str().c_str(), 
																										SDL_BLACK);
			applySurface(WINDOW_WIDTH-200, WINDOW_HEIGHT-50+i*25, hpSurface, screen);
		}

		// BUTTONS
		/*
		for (unsigned int i = 0; i < MAX_BUTTON_COUNT; i++) {
			if (buttons[i] && !buttons[i]->isClicked()) {
				buttons[i]->show();
			}
		}
		*/
		// MESSAGES

		for (unsigned int i = 0; i < MAX_BUTTON_COUNT; i++) {
			if (buttons[i] && buttons[i]->isClicked()) {
				if (i < MAX_MESSAGE_COUNT && messages[i]) {
					applySurface(150, 10, messages[i], screen);
				}

				buttons[i]->timeUntilDisplay--;
			}
		}		
	}

	// MENUS

	if (g->b && !g->b->battleMenu.empty()) {
		int i = 0;
		for (vector<int>::const_iterator iter = g->b->battleMenu.begin(); 
				 iter != g->b->battleMenu.end(); iter++, i++) {
			SDL_Surface *miSurface = TTF_RenderText_Solid(
				font24, g->b->getMenuItemName(*iter).c_str(), SDL_BLACK);
			applySurface(20, WINDOW_HEIGHT-50+i*25, miSurface, screen);
		}
	}

	// update the screen
	if(SDL_Flip(screen)== -1) {
		cout << "unable to flip screen" << endl;
		exit(EXIT_FAILURE);
	}
}

void MyWindow::toggleMusic() {
	if (music == NULL) {
		music = Mix_LoadMUS("assets/music/senomar.mid");

		// play infinite times
		Mix_PlayMusic(music, -1);
	} else {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}
}
