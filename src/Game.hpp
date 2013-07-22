// Hari Ganesan 7/21/13
// zombie-roll: Game library file

#include "Battle.hpp"

class Game {
	int music;
	int background;
	unsigned int requiredXP[MAX_LEVEL_COUNT];

public:
	int display;
	int timer;
	int partyCount;
	vector<PartyMember> party;
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
	void setLevels();
};
