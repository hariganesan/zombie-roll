// Hari Ganesan 3/10/13
// zombie-roll: actor cpp file

#include "Actor.hpp"

// TODO: add objects/borders so that returns false
bool Character::moveLeft() {
	x -= F_BOX_DIM;
	orig_x = x;

	return true;
}

bool Character::moveDown() {
	y += F_BOX_DIM;
	orig_y = y;

	return true;
}

bool Character::moveRight() {
	x += F_BOX_DIM;
	orig_x = x;

	return true;
}

bool Character::moveUp() {
	y -= F_BOX_DIM;
	orig_y = y;

	return true;
}

unsigned int FightingCharacter::getLevel() const {
	return level;
}

unsigned int FightingCharacter::getXp() const {
	return xp;
}

int FightingCharacter::getAttack() const {
	return attack;
}

int FightingCharacter::getDefense() const {
	return defense;
}

int FightingCharacter::getMagic() const {
	return magic;
}

int FightingCharacter::getSpeed() const {
	return speed;
}

unsigned int FightingCharacter::getTotalHP() const {
	return totalHP;
}

unsigned int FightingCharacter::getTotalMP() const {
	return totalMP;
}

unsigned int FightingCharacter::getRemainingHP() const {
	return remainingHP;
}

unsigned int FightingCharacter::getRemainingMP() const {
	return remainingMP;
}

unsigned int FightingCharacter::getCT() const {
	return ct;
}

bool FightingCharacter::takeDamage(unsigned int dmg) {
	if (remainingHP - dmg < 0) {
		remainingHP = 0;
		return false;
	}

	remainingHP -= dmg;
	return true;
}

bool FightingCharacter::useMP(int mp) {
	if (remainingMP - mp < 0) {
		return false;
	}

	remainingMP -= mp;
	return true;
}

bool FightingCharacter::setCT(int newCT) {
	if (newCT < 0 || newCT > 100) {
		std::cerr << "Actor.cpp/105: ct out of bounds" << std::endl;
		return false;
	}

	ct = (unsigned) newCT;
	return true;
}

void FightingCharacter::printStatus() const {
	// print name, level \ hp, mp \ att, def, mag, spe
	cout << id << ", L" << level << endl;
	cout << "HP: " << remainingHP << "/" << totalHP;
	cout << ", MP: " << remainingMP << "/" << totalMP << endl;
	cout << "A: " << attack << " D: " << defense;
	cout << " M: " << magic << " S: " << speed << endl;
}
