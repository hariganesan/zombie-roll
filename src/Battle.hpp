// Hari Ganesan 3/20/13
// zombie-roll: Battle library file

#include "Actor.hpp"
#include <vector>
#include <list>

using std::vector;
using std::list;

class Game;

class View {
	string id;
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

class Battle {
	int music;
	int background;

public:
	Game *g; // access to public game members (party, etc.)
	Area *a; // access to public area members

	int enemyCount;
	vector<Enemy> enemies; // enemy list
	list<FightingCharacter> bQueue;// battle queue

	Battle(Game *g, int ec);
	~Battle();
	void fillBQueue();
	bool checkHit(const FightingCharacter& c1, const FightingCharacter& c2);
	unsigned int calculateDamage(const FightingCharacter& c1, const FightingCharacter& c2);
	// returns true if should advance to next turn
	bool attack(FightingCharacter& c1, FightingCharacter& c2, int mp);

};

