// Hari Ganesan 7/21/13
// zombie-roll: Game class

#include "Game.hpp"

Game::Game(string d, int p) : timer(0), currentArea(NULL), b(NULL) {
	display = p;

	// create MC
	party.push_back(PartyMember(d, MC_ATT_INIT, MC_DEF_INIT, 
															MC_MAG_INIT, MC_SPE_INIT));

	// create PM1
	party.push_back(PartyMember("Rai", PM1_ATT_INIT, PM1_DEF_INIT, 
															PM1_MAG_INIT, PM1_SPE_INIT));

	mc = &party[0];
	// field use
	mc->setPosition(200, 200);
	mc->setSpriteRowCount(2);
	mc->setSpriteColCount(2);

	// set EXP and levels for all party members
	setLevels();
}

Game::~Game() {
	destroyArea();
	destroyBattle();

	// remove party members
	vector<PartyMember>::iterator iter = party.begin();
	while (iter != party.end()) {
		iter = party.erase(iter);
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
		b = new Battle(currentArea->calcEnemyCount());
		b->a = currentArea;
		b->party = party; // TODO: check vector copying - change to explicit?
	}	else {
		cerr << "Battle.cpp/57: previous battle not destroyed" << endl;
		return;
	}
}

void Game::destroyBattle() {
	if (b) {
		Battle *tmp = b;
		b = NULL;
		delete tmp;
	}
}

void Game::setLevels() {
	double B=log((double)REQ_XP_MAX_LEVEL/REQ_XP_INIT_LEVEL)/(MAX_LEVEL_COUNT-2);
	double A=(double)REQ_XP_INIT_LEVEL/(exp(B)-1.0);

	for (unsigned int i = 0; i < MAX_LEVEL_COUNT; i++) {
		requiredXP[i] = round(A*(exp(B*(i-1))-1));
	}
}
