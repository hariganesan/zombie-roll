// Hari Ganesan 7/22/13
// zombie-roll: loading and rendering assets

#include "Render.hpp"

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

void MyWindow::pushDots() {
	spriteSheets[0] = loadImage("../../Desktop/dots.png");
	SDL_Surface *dots = spriteSheets[0];
	SDL_Rect clip[MAX_SPRITE_ROW_COUNT*MAX_SPRITE_COL_COUNT];

	for (unsigned int i = 0; i < MAX_SPRITE_ROW_COUNT; i++) {
		for (unsigned int j = 0; j < MAX_SPRITE_COL_COUNT; j++) {
			clip[MAX_SPRITE_ROW_COUNT*i+j].x = j*SPRITE_WIDTH;
			clip[MAX_SPRITE_ROW_COUNT*i+j].y = i*SPRITE_HEIGHT;
			clip[MAX_SPRITE_ROW_COUNT*i+j].w = SPRITE_WIDTH;
			clip[MAX_SPRITE_ROW_COUNT*i+j].h = SPRITE_HEIGHT;
		}
	}

	// fill the screen white
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

	// apply the sprites to the screen
	applySurface(0, 0, dots, screen, &clip[0]);
	applySurface(540, 0, dots, screen, &clip[1]);
	applySurface(0, 380, dots, screen, &clip[2]);
	applySurface(540, 380, dots, screen, &clip[3]);

	// update the screen
	if(SDL_Flip(screen)== -1) {
		cout << "unable to flip screen" << endl;
		exit(EXIT_FAILURE);
	}
}

void MyWindow::renderSDL() {
	if (g->display == D_FIELD) {
		// DRAW MC

		Vec2d mcPos = g->mc->getPosition();
		unsigned int sprite = g->mc->getSprite();
		SDL_Rect clip;
		clip.x = (sprite - sprite/g->mc->getSpriteColCount())*100; // fIX
		clip.y = sprite/g->mc->getSpriteRowCount()*100;
		clip.w = SPRITE_WIDTH;
		clip.h = SPRITE_HEIGHT;

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

		// get spritesheet 0 and attach MC to screen
		applySurface(mcPos.x, mcPos.y, spriteSheets[0], screen, &clip);
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
