// Hari Ganesan 3/20/13
// zombie-roll: Battle class

#include "Battle.hpp"

Battle::Battle() : enemyCount(0) {
	for (int i = 0; i < MAX_ENEMY_COUNT; i++) {
		enemies[i] = NULL;
	}
}

Battle::~Battle() {
	for (int i = 0; i < MAX_ENEMY_COUNT; i++) {
		if (enemies[i]) {
			Enemy *tmp = enemies[i];
			enemies[i] = NULL;
			delete tmp;
		}
	}

}

Game::Game(string d, int p) : timer(0), currentArea(NULL), b(NULL) {
	display = p;
	mc = new FieldCharacter(d);

	for (int i = 0; i < MAX_PARTY_COUNT; i++) {
		party[i] = NULL;
	}
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
		b->addEnemy(new Enemy("zombie"));
	}

	return;
}
