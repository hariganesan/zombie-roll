// Hari Ganesan 3/10/13
// zombie-roll: actor library file

#include "Elements.hpp"

const int MAX_PARTY_COUNT = 4;
const int MAX_ENEMIES_COUNT = 4;

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
public:
	RenderableActor(string d);
	void draw();
};

class Item : public RenderableActor {
	string description;

public:
	Item(string d);
};

class Equippable : public RenderableActor {
	int weight;
	string description;
public:
	Equippable(string d);
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

public:
	Weapon(string d);
};

class Armor : public Equippable {
	enum {
		AR_HEAD,
		AR_BODY
	};

	int armorClass;
	int defense;

public:
	Armor(string d);
};

class Character : public RenderableActor {
	bool isSpeaking;
public:
	Character(string d);
};

class FieldCharacter : public Character {
	int sprite;

public:
	// position in field
	int orig_x;
	int orig_y;
	int x;
	int y;

	FieldCharacter(string d) : Character(d), orig_x(0), orig_y(0), x(0), y(0) {};
	bool moveLeft(); // returns true if moved
	bool moveDown();
	bool moveRight();
	bool moveUp();
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

	Weapon *equippedWeapon;
	Armor *equippedArmor[2];
public:
	FightingCharacter(string d, int l, int a, int f, int m, int s, int h, int n) : Character(d), exp(0) {
		level = l;
		attack = a;
		defense = f;
		magic = m;
		speed = s;
		totalHP = h;
		totalMP = n;
	}
	FightingCharacter(string d) : Character(d), exp(0) {};
};

class PartyMember : public FightingCharacter {
	Vec2d menuLocation;

public:
	PartyMember(string d, int l, int a, int f, int m, int s, int h, int n);
};

class Enemy : public FightingCharacter {
	int intelligence;

public:
	Enemy(string d, int l, int a, int f, int m, int s, int h, int n);
	Enemy(string d) : FightingCharacter(d) {};
};
