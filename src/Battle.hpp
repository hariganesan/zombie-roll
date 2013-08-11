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

	unsigned int calcEnemyCount() {return rand() % 3 + 1; };
};

class Battle {
	unsigned int music;
	unsigned int background;

	enum {
		BMENU_ATTACK,
		BMENU_DEFEND,
		BMENU_SKILL,
		BMENU_ITEM
	};

public:
	Game *g; // access to public game members (party, etc.)
	Area *a; // access to public area members

	vector<PartyMember> party; // party list copied from game
	vector<Enemy> enemies; // enemy list
	list<FightingCharacter> bQueue;// battle queue
	FightingCharacter *activeFC; // current FC turn
	vector<int> battleMenu; // battle menu for PMs
	int selectedBattleMenuItem; // highlighted item

	Battle(int ec);
	~Battle();
	void bQueuePush();
	FightingCharacter* bQueuePop();
	bool checkHit(const FightingCharacter& c1, const FightingCharacter& c2);
	unsigned int calculateDamage(const FightingCharacter& c1, 
															 const FightingCharacter& c2);
	// returns true if should advance to next turn
	bool attack(FightingCharacter& c1, FightingCharacter& c2, int mp);
	string getMenuItemName(const int& item) const;

};
