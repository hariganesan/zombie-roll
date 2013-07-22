// Hari Ganesan 3/20/13
// zombie-roll: Battle library file

#include "Actor.hpp"

class Game;

class View {
	string id;
};

class Battle {
	int music;
	int background;

public:
	int enemyCount;

	Game *g; // access to public game functions
	Enemy *enemies[MAX_ENEMY_COUNT];

	Battle();
	~Battle();
	void addEnemy(Enemy *e);
	bool checkHit(const FightingCharacter& c1, const FightingCharacter& c2);
	unsigned int calculateDamage(const FightingCharacter& c1, const FightingCharacter& c2);
	bool attack(FightingCharacter& c1, FightingCharacter& c2, int mp);

};

class Area {
public:
	double averageEnemyLevel;
	double battlePercent;

	Area(double b) {
		battlePercent = b;
	}

	int calcEnemyCount() {return rand() % 3 + 1; };
};
