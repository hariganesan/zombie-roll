// Hari Ganesan 3/20/13
// zombie-roll: Battle class

#include <string>
#include "Actor.hpp"

using namespace std;

class View {
	string id;
};

class Battle : public View {
	int music;
	int background;
	int enemiesCount;
};

class Game {
public:
	FieldCharacter *mc;

	Game() {
		mc = new FieldCharacter("mc");
	}
};
