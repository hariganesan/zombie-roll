// Hari Ganesan 3/20/13
// zombie-roll: Battle class

#include "Battle.hpp"

Battle::Battle(int ec) : activeFC(NULL) {
	for (int i = 0; i < ec; i++) {
		enemies.push_back(Enemy("Zombie"));
	}

	// fill the battle queue
	while (bQueue.size() < MAX_BQUEUE_ITEMS) {
		bQueuePush();
	}

	// pop first member and push into activeFC
	if (!(activeFC = bQueuePop())) { // TODO: not getting right fc, fix
		cerr << "Battle.cpp/18: no items in battle queue" << endl;
		exit(1);
	}

	if (activeFC->isPartyMember) {
		// createBattleMenu();
		battleMenu.push_back(BMENU_ATTACK);
		battleMenu.push_back(BMENU_DEFEND);
	} else {
		// make sure menu is empty?
	}

	bQueuePush();
}

Battle::~Battle() {
	// remove enemies
	vector<Enemy>::iterator iter = enemies.begin();
	while (iter != enemies.end()) {
		iter = enemies.erase(iter);
	}
}

void Battle::bQueuePush() {
	if (bQueue.size() > MAX_BQUEUE_ITEMS) {
		cerr << "Battle.cpp/30: bQueue overflow" << endl;
	}

	// get next ctTable member at 100
	unsigned int lowestCyclesNeeded = MAX_CYCLE;

	// cycle through both party and enemies
	for (vector<PartyMember>::const_iterator iter = party.begin();
			 iter != party.end(); iter++) {
		if ((MAX_CYCLE-iter->getCT())/iter->getSpeed()*SPEED_CONSTANT < lowestCyclesNeeded) {
			lowestCyclesNeeded = (MAX_CYCLE-iter->getCT())/iter->getSpeed()*SPEED_CONSTANT;
		}
	}
	for (vector<Enemy>::const_iterator iter = enemies.begin();
			 iter != enemies.end(); iter++) {
		if ((MAX_CYCLE-iter->getCT())/iter->getSpeed()*SPEED_CONSTANT < lowestCyclesNeeded) {
			lowestCyclesNeeded = (MAX_CYCLE-iter->getCT())/iter->getSpeed()*SPEED_CONSTANT;
		}
	}

	// edit ct values
	for (vector<PartyMember>::iterator iter = party.begin();
			 iter != party.end(); iter++) {
		iter->setCT(iter->getCT()+iter->getSpeed()*SPEED_CONSTANT*lowestCyclesNeeded);
	}
	for (vector<Enemy>::iterator iter = enemies.begin();
			 iter != enemies.end(); iter++) {
		iter->setCT(iter->getCT()+iter->getSpeed()*SPEED_CONSTANT*lowestCyclesNeeded);
	}

	// push back character with lowest attack
	FightingCharacter *fc = NULL;
	for (vector<PartyMember>::iterator iter = party.begin();
			 iter != party.end(); iter++) {
		if (iter->getCT() == 100) {
			if (!fc || iter->getAttack() > fc->getAttack()) {
				fc = &(*iter);
			}
		}
	}
	for (vector<Enemy>::iterator iter = enemies.begin();
			 iter != enemies.end(); iter++) {
		if (iter->getCT() == 100) {
			if (!fc || iter->getAttack() > fc->getAttack()) {
				fc = &(*iter);
			}
		}
	}

	if (fc) {
		bQueue.push_back(*fc);
	} else {
		cerr << "Battle.cpp/70: no FC pushed to queue" << endl;
	}
}

FightingCharacter* Battle::bQueuePop() {
	if (!bQueue.empty()) {
		FightingCharacter *fc = &bQueue.front();
		bQueue.pop_front();
		return fc;
	}

	return NULL;	
}

bool Battle::checkHit(const FightingCharacter& c1, 
											const FightingCharacter& c2) {
	// use arctan fn
	double hitPercent = 2/M_PI*atan(7*c1.getSpeed()/c2.getSpeed());

	if (rand() % 1000 < hitPercent*1000)
		return true;

	return false;
}

unsigned int Battle::calculateDamage(const FightingCharacter& c1, 
																		 const FightingCharacter& c2) {
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

string Battle::getMenuItemName(const int& item) const {
	switch (item) {
		case BMENU_ATTACK: return "Attack";
		case BMENU_DEFEND: return "Defend";
		case BMENU_SKILL: return "Skill";
		case BMENU_ITEM: return "Item";
		default: return "???";
	}
}
