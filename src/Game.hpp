// Hari Ganesan 7/21/13
// zombie-roll: Game library file

#include "Battle.hpp"

class Game {
	unsigned int music;
	unsigned int background;
	unsigned int requiredXP[MAX_LEVEL_COUNT];

public:
	unsigned int display; // used for game logic
	unsigned int timer; // used for transitions
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
