// Hari Ganesan 7/21/13
// zombie-roll: Game library file

#include "Battle.hpp"

class Game {
	int music;
	int background;
	unsigned int requiredXP[MAX_LEVEL_COUNT];

public:
	int display; // used for game logic
	int timer; // used for transitions
	int partyCount; // delete? could use party.size()
	vector<PartyMember> party;
	PartyMember *mc;
	Area *currentArea;
	Battle *b;

  Game(string d, int p);
  ~Game();
  void destroyArea();
	void createBattle();
	void destroyBattle();
	void setLevels();
};
