// Hari Ganesan 3/10/13
// zombie-roll: actor cpp file

#include "Actor.hpp"

using std::cout;
using std::endl;

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

void FightingCharacter::printStatus() {
	// print name, level \ hp, mp \ att, def, mag, spe
	cout << id << ", L" << level << endl;
	cout << "HP: " << remainingHP << "/" << totalHP;
	cout << ", MP: " << remainingMP << "/" << totalMP << endl;
	cout << "A: " << attack << " D: " << defense;
	cout << " M: " << magic << " S: " << speed << endl;

}
