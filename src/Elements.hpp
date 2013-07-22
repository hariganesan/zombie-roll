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

// battle queue
const unsigned int MAX_BQUEUE_ITEMS = 8;
const unsigned int MAX_CYCLE = 100;
const double SPEED_CONSTANT = 1.0;

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

// SPRITE SHEETS
const int MAX_SPRITE_SHEET_COUNT = 1;

// CHARACTERS
const int MAX_PARTY_COUNT = 4;
const int MAX_ENEMY_COUNT = 4;

const int MC_ATT_INIT = 4;
const int MC_DEF_INIT = 7;
const int MC_MAG_INIT = 0;
const int MC_SPE_INIT = 4;

const int PM1_ATT_INIT = 4;
const int PM1_DEF_INIT = 4;
const int PM1_MAG_INIT = 0;
const int PM1_SPE_INIT = 7;


// LEVELING
const int MAX_LEVEL_COUNT = 101;
const int REQ_XP_INIT_LEVEL = 50;
const int REQ_XP_MAX_LEVEL = 10000;


// STATUSES
// PM = party member, EN = enemy
enum {
	SC_MC,
	SC_PM1,
	SC_PM2,
	SC_PM3,
	SC_EN1
};

// FIELD
enum {
	SF_FRONT,
	SF_BACK,
	SF_LEFT,
	SF_RIGHT
};

// BATTLE
enum {
	SB_NORMAL,
	SB_POISON,
	SB_DARKNESS,
	SB_CONFUSION,
	SB_SILENCE,
	SB_BLEED,
	SB_BESERK,
	SB_DRUNK,
	SB_OVERDRIVE
};

// ATB system
//


// DISPLAYS
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
