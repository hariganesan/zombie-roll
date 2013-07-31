// Hari Ganesan 7/24/13
// zombie-roll: buttons

#include "../main/Window.hpp"

Button::Button(SDL_Surface *bs, SDL_Surface *s, int x, int y, int w, int h)
						 : buttonSheet(bs), screen(s), timeUntilDisplay(0) {
	// set attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	//Clip the sprite sheet (here into 4)
	clips[ CLIP_MOUSE_OVER ].x = 0;
	clips[ CLIP_MOUSE_OVER ].y = 0;
	clips[ CLIP_MOUSE_OVER ].w = w;
	clips[ CLIP_MOUSE_OVER ].h = h;

	clips[ CLIP_MOUSE_OUT ].x = w;
	clips[ CLIP_MOUSE_OUT ].y = 0;
	clips[ CLIP_MOUSE_OUT ].w = w;
	clips[ CLIP_MOUSE_OUT ].h = h;

	clips[ CLIP_MOUSE_DOWN ].x = 0;
	clips[ CLIP_MOUSE_DOWN ].y = h;
	clips[ CLIP_MOUSE_DOWN ].w = w;
	clips[ CLIP_MOUSE_DOWN ].h = h;

	clips[ CLIP_MOUSE_UP ].x = w;
	clips[ CLIP_MOUSE_UP ].y = h;
	clips[ CLIP_MOUSE_UP ].w = w;
	clips[ CLIP_MOUSE_UP ].h = h;

	clip = &clips[CLIP_MOUSE_OUT];
}

Button::~Button() {
	if (buttonSheet) {
		SDL_Surface *tmpBS = buttonSheet;
		buttonSheet = NULL;
		SDL_FreeSurface(tmpBS);
	}
}

bool Button::handleEvent(SDL_Event e) {
	int x = 0; int y = 0; // mouse offsets

	if (e.type == SDL_MOUSEMOTION) {
		x = e.motion.x;
		y = e.motion.y;

		// if mouse is over button, set button sprite
		if((x > box.x) && (x < box.x+box.w) && (y > box.y) && (y < box.y+box.h)) {
			clip = &clips[CLIP_MOUSE_OVER];
		} else {
			clip = &clips[CLIP_MOUSE_OUT];
		}
	} else if (e.type == SDL_MOUSEBUTTONDOWN && 
						 e.button.button == SDL_BUTTON_LEFT) {
		x = e.button.x;
		y = e.button.y;

		if((x > box.x) && (x < box.x+box.w) && (y > box.y) && (y < box.y+box.h)) {
			clip = &clips[CLIP_MOUSE_DOWN];
		}
	} else if (e.type == SDL_MOUSEBUTTONUP &&
						 e.button.button == SDL_BUTTON_LEFT) {
		x = e.button.x;
		y = e.button.y;

		if((x > box.x) && (x < box.x+box.w) && (y > box.y) && (y < box.y+box.h)) {
			if (clip == &clips[CLIP_MOUSE_DOWN]) {
				click();
				clip = &clips[CLIP_MOUSE_UP]; // consider removing
				return true;
			}
		}
	}

	return false;
}

void Button::show() {
	SDL_Rect offset; // holds offsets

	// get offsets
	offset.x = box.x;
	offset.y = box.y;

	SDL_BlitSurface(buttonSheet, clip, screen, &offset);
}

void Button::click() {
	timeUntilDisplay = (signed) SDL_FRAME_RATE*MESSAGE_DISPLAY_TIME;
	//messageOnScreen = message;
}

bool Button::isClicked() {
	if (timeUntilDisplay > 0) {
		return true;
	}

	return false;
}
