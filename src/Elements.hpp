// Hari Ganesan 3/21/13
// zombie-roll: elements

#include <iostream>
#include <string>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_opengl.h"
#include "SDL_ttf/SDL_ttf.h"

// window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MARGIN = 10;


const int SDL_FRAME_RATE = 30;
const int F_BOX_DIM = 20; // field box dimension
const double FIELD_COLOR = 0.3;

// transition time
const int TT_FIELD_BATTLE = 75;

// display options

// locations - battle screen
// character locations
const int LB_BOX_CHARS_X = 0;
const int LB_BOX_CHARS_Y = 0;
const int LB_BOX_CHARS_W = 0;
const int LB_BOX_CHARS_H = 0;

const int LB_CHAR_PARTY_1 = 0;
const int LB_CHAR_PARTY_2 = 0;
const int LB_CHAR_PARTY_3 = 0;
const int LB_CHAR_PARTY_4 = 0;

const int LB_CHAR_ENEMY_1 = 0;
const int LB_CHAR_ENEMY_2 = 0;
const int LB_CHAR_ENEMY_3 = 0;
const int LB_CHAR_ENEMY_4 = 0;

// statuses
const int LB_BOX_SBAR_X = 0;
const int LB_BOX_SBAR_Y = 0;
const int LB_BOX_SBAR_W = 0;
const int LB_BOX_SBAR_H = 0;

const int LB_SBAR_PARTY_1 = 0;
const int LB_SBAR_PARTY_2 = 0;
const int LB_SBAR_PARTY_3 = 0;
const int LB_SBAR_PARTY_4 = 0;

const int LB_SBAR_ENEMY_1 = 0;
const int LB_SBAR_ENEMY_2 = 0;
const int LB_SBAR_ENEMY_3 = 0;
const int LB_SBAR_ENEMY_4 = 0;

// status bar components (within the bar)
const int LSBAR_HEALTH_BAR = 0;
const int LSBAR_INDICATOR_HP = 0;
const int LSBAR_INDICATOR_MP = 0;
const int LSBAR_OVERDRIVE_BAR = 0;

// ATB system
//


enum {
	// main displays
	D_MAIN,
	D_HOME,
	D_FIELD,
	D_BATTLE,
	// display transitions
	DT_FIELD_BATTLE,
	DT_BATTLE_FIELD
};

// events to be used to hold info for game logic
struct Keys {
	bool right;
	bool left;
	bool up;
	bool down;
};
