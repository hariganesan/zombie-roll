// Hari Ganesan 3/21/13
// zombie-roll: elements

const int F_BOX_DIM = 20; // field box dimension
const int SDL_FRAME_RATE = 30;

const double FIELD_COLOR = 0.3;

// transition time
const int TT_FIELD_BATTLE = 75;

// display options
enum {
	D_HOME,
	D_FIELD,
	D_BATTLE,
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
