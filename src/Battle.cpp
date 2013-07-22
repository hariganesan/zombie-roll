// Hari Ganesan 3/20/13
// zombie-roll: Battle class

#include "Battle.hpp"

using std::cout;
using std::endl;

Battle::Battle(Game *g, int ec) : g(g), enemyCount(ec) {
	for (int i = 0; i < ec; i++) {
		enemies.push_back(Enemy("Zombie"));
	}

	// fill the battle queue
	fillBQueue();
}

Battle::~Battle() {
	// remove enemies
	vector<Enemy>::iterator iter = enemies.begin();
	while (iter != enemies.end()) {
		iter = enemies.erase(iter);
	}
}

void Battle::fillBQueue() {

	while (bQueue.size() < MAX_BQUEUE_ITEMS) {
		// get next ctTable member at 100
		//int highestCtSoFar = 0;

		//bQueue.push_back(fc);
	}
}

bool Battle::checkHit(const FightingCharacter& c1, const FightingCharacter& c2) {
	// use arctan fn
	double hitPercent = 2/M_PI*atan(7*c1.getSpeed()/c2.getSpeed());

	if (rand() % 1000 < hitPercent*1000)
		return true;

	return false;
}

unsigned int Battle::calculateDamage(const FightingCharacter& c1, const FightingCharacter& c2) {
	int att = c1.getAttack();
	int def = c2.getDefense();

	unsigned int damage = (pow(att, 2)*15+5*rand()%att)/(def*15+5*rand()%def+20);

	return damage;
}

bool Battle::attack(FightingCharacter& c1, FightingCharacter& c2, int mp) {
	// check for MP use
	if (!c1.useMP(mp)) {
		cout << "insufficient MP" << endl;
		return false;
	}

	if (!checkHit(c1, c2)) {
		// run miss/evade sequence
		cout << "attack missed!" << endl;
		return true;
	}

	// subtract HP from c2
	if (!c2.takeDamage(calculateDamage(c1, c2))) {
		// run faint sequence
		cout << "character fainted" << endl;

		// if party member, check to see if all are fainted
		// if all party fainted, run game over sequence
		return false;
	}

	// attack successful!
	cout << "attack hit" << endl;
	return true;
}
