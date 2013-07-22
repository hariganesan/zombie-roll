// Hari Ganesan 7/21/13
// zombie-roll: Game class

#include "Game.hpp"

Game::Game(string d, int p) : timer(0), partyCount(1), currentArea(NULL), b(NULL) {
	for (int i = 0; i < MAX_PARTY_COUNT; i++) {
		party[i] = NULL;
	}

	display = p;

	// create MC
	mc = new PartyMember(d, MC_ATT_INIT, MC_DEF_INIT, MC_MAG_INIT, MC_SPE_INIT);
	party[0] = mc;

	// set EXP and levels
	setLevels();
}

Game::~Game() {
	destroyArea();
	destroyBattle();

	for (int i = 0; i < MAX_PARTY_COUNT; i++) {
		if (party[i]) {
			PartyMember *tmp = party[i];
			party[i] = NULL;
			delete tmp;
		}
	}
}

void Game::destroyArea() {
	if (currentArea) {
		Area *tmp = currentArea;
		currentArea = NULL;
		delete tmp;
	}
}

void Game::createBattle() {
	if (!b) {
		b = new Battle();
		b->g = this;
	}	else {
		std::cerr << "Battle.cpp/57: previous battle not destroyed" << std::endl;
	}
}

void Game::destroyBattle() {
	if (b) {
		Battle *tmp = b;
		b = NULL;
		delete tmp;
	}
}

void Game::randomBattle() {
	int enemyCount = currentArea->calcEnemyCount();
	createBattle();

	for (int i = 0; i < enemyCount; i++) {
		b->addEnemy(new Enemy("Zombie"));
	}
}

void Game::setLevels() {
	double B = log((double)REQ_XP_MAX_LEVEL/REQ_XP_INIT_LEVEL)/(MAX_LEVEL_COUNT-2);
	double A = (double)REQ_XP_INIT_LEVEL/(exp(B)-1.0);

	for (int i = 0; i < MAX_LEVEL_COUNT; i++) {
		requiredXP[i] = round(A*(exp(B*(i-1))-1));
	}
}
