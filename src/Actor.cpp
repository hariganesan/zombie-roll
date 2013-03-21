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

void FieldCharacter::moveLeft() {
	x -= F_BOX_DIM;
}

void FieldCharacter::moveDown() {
	y += F_BOX_DIM;
}

void FieldCharacter::moveRight() {
	x += F_BOX_DIM;
}

void FieldCharacter::moveUp() {
	y -= F_BOX_DIM;
}
