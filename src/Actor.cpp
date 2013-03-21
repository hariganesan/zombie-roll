// Hari Ganesan 3/10/13
// zombie-roll: actor cpp file

#include "Actor.hpp"

Actor::Actor(string d) {
	id = d;
}

RenderableActor::RenderableActor(string d) : Actor(d) {
}

Character::Character(string d) : RenderableActor(d) {
}

// TODO: add objects/borders so that returns false
bool FieldCharacter::moveLeft() {
	x -= F_BOX_DIM;

	return true;
}

bool FieldCharacter::moveDown() {
	y += F_BOX_DIM;

	return true;
}

bool FieldCharacter::moveRight() {
	x += F_BOX_DIM;

	return true;
}

bool FieldCharacter::moveUp() {
	y -= F_BOX_DIM;

	return true;
}
