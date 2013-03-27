// Hari Ganesan 3/20/13
// zombie-roll: Battle library file

#include <string>
#include "Actor.hpp"
#include "SDL/SDL_image.h"
#include "SDL/SDL_opengl.h"

using namespace std;

class View {
	string id;
};

class Battle : public View {
	int music;
	int background;
public:
	int partyCount;
	PartyMember* party[MAX_PARTY_COUNT];
	int enemiesCount;
	Enemy* enemies[MAX_ENEMIES_COUNT];

	Battle(int p) : enemiesCount(0) {
		partyCount = p;
	}

	void addEnemy(Enemy *e) {
		enemies[enemiesCount] = e;
		enemiesCount++;
	}
};

class Area {
public:
	int averageEnemyLevel;
	double battlePercent;

	Area(double b) {
		battlePercent = b;
	}

	int calcEnemiesCount() {return rand() % 3 + 1; };
};

class Game {
	int music;
	int background;
	int partyCount;
	PartyMember** party;

public:
	int display;
	int timer;
	FieldCharacter *mc;
	Area *currentArea;
	GLuint png;

	Game(string d, int p) : timer(0), currentArea(NULL) {
		display = p;
		mc = new FieldCharacter(d);
	}

	Battle *randomBattle();
};
