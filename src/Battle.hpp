// Hari Ganesan 3/20/13
// zombie-roll: Battle library file

#include <string>
#include "Actor.hpp"

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
	FieldCharacter *mc;
	Area *currentArea;

	Game(string d, int p) : currentArea(NULL) {
		mc = new FieldCharacter(d);
		display = p;
	}

	Battle *randomBattle();
};
