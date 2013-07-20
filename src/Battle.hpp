// Hari Ganesan 3/20/13
// zombie-roll: Battle library file

#include "Actor.hpp"

class View {
	string id;
};

class Battle {
	int music;
	int background;

public:
	int enemyCount;
	Enemy *enemies[MAX_ENEMY_COUNT];

	Battle();
	~Battle();
	void addEnemy(Enemy *e) {
		enemies[enemyCount] = e;
		enemyCount++;
	}
};

class Area {
public:
	int averageEnemyLevel;
	double battlePercent;

	Area(double b) {
		battlePercent = b;
	}

	int calcEnemyCount() {return rand() % 3 + 1; };
};

class Game {
	int music;
	int background;

public:
	int display;
	int timer;
	int partyCount;
	PartyMember *party[MAX_PARTY_COUNT];
	PartyMember *mc;
	Area *currentArea;
	GLuint spriteSheets[MAX_SPRITE_SHEET_COUNT];
	Battle *b;

  Game(string d, int p);
  ~Game();
  void destroyArea();
	void createBattle();
	void destroyBattle();
	void randomBattle();
};
