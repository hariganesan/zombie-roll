// Hari Ganesan 3/20/13
// zombie-roll: Battle class

#include "Battle.hpp"

Game::Game(string d, int p) : timer(0), currentArea(NULL) {
	display = p;
	mc = new FieldCharacter(d);
}

Battle *Game::randomBattle() {
	int enemiesCount = currentArea->calcEnemiesCount();
	Battle *b = new Battle(partyCount);

	for (int i = 0; i < enemiesCount; i++) {
		b->addEnemy(new Enemy("zombie"));
	}

	return b;
}
