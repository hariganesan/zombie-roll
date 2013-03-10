// Hari Ganesan 3/10/13
// zombie-roll: actor library file

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

struct Vec2d {
	int x;
	int y;
};

class Actor {
	string id;
	Vec2d position;

public:
	Actor(string d);
};

class RenderableActor : public Actor {
	void draw();
};

class Item : public RenderableActor {
	string description;
};

class Equippable : public RenderableActor {
	int weight;
	string description;
};

class Weapon : public Equippable {
	enum {
		WP_SWORD,
		WP_AXE,
		WP_BOW,
		WP_DAGGER
	};

	int weaponClass;
	int attack;
};

class Armor : public Equippable {
	enum {
		AR_HEAD,
		AR_BODY
	};

	int armorClass;
	int defense;
};

class Character : public RenderableActor {
	bool isSpeaking;
};

class FightingCharacter : public Character {
	// stats
	int level;
	int exp;
	int attack;
	int defense;
	int magic;
	int speed;
	int totalHP;
	int totalMP;

	enum {	
		STATUS_NORMAL,
		STATUS_POISONED,
		STATUS_FROZEN,
		STATUS_BURNED,
		STATUS_ASLEEP
	};

	// status
	int remainingHP;
	int remainingMP;
	int status;

	Weapon equippedWeapon;
	Armor equippedArmor[2];
};

class PartyMember : public FightingCharacter {
	Vec2d menuLocation;
};

class Enemy : public FightingCharacter {
	int intelligence;
};
