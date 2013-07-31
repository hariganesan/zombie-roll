// Hari Ganesan 3/10/13
// zombie-roll: actor library file

#include "Elements.hpp"
#include <iostream>
#include <string>
#include <cmath>

using std::cin;					using std::cout;
using std::cerr;				using std::endl;
using std::string;

struct Vec2d {
	int x;
	int y;
};

class Actor {
protected:
	string id; // change to const char*?
	Vec2d pos;

public:
	Actor(string d) : id(d) {};
	string getID() const { return id;};
	Vec2d getPosition() const {return pos;};
	void setPosition(int x, int y) {pos.x = x; pos.y = y;};
};

class RenderableActor : public Actor {
public:
	RenderableActor(string d) : Actor(d) {};
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
	unsigned int sprite;
	unsigned int spriteCount;
	unsigned int spriteRowCount;
	unsigned int spriteColCount;

	enum {
		SPRITE_DOWN,
		SPRITE_LEFT,
		SPRITE_RIGHT,
		SPRITE_UP
	};

public:
	Character(string d) : RenderableActor(d), sprite(SPRITE_RIGHT) {};
	bool moveLeft(); // returns true if moved
	bool moveDown();
	bool moveRight();
	bool moveUp();
	unsigned int getSprite() const;
	unsigned int getSpriteRowCount() const;
	void setSpriteRowCount(unsigned int s);
	unsigned int getSpriteColCount() const;
	void setSpriteColCount(unsigned int s);
};

class FightingCharacter : public Character {
	// stats
	unsigned int level;
	unsigned int xp;
	int attack;
	int defense;
	int magic;
	int speed;
	unsigned int totalHP;
	unsigned int totalMP;

	enum {	
		STATUS_NORMAL,
		STATUS_POISONED,
		STATUS_FROZEN,
		STATUS_BURNED,
		STATUS_ASLEEP
	};

	// status
	unsigned int remainingHP;
	unsigned int remainingMP;
	unsigned int status;
	unsigned int ct;

	Weapon *equippedWeapon;
	Armor *equippedArmor[2];
public:
	FightingCharacter(string d, int a, int f, int m, int s, 
										int l = 1, int h = 25, int n = 10) : Character(d), xp(0)
										, remainingHP(h), remainingMP(n), status(0), ct(0) {
		level = l;
		attack = a;
		defense = f;
		magic = m;
		speed = s;
		totalHP = h;
		totalMP = n;

		equippedWeapon = NULL;
		equippedArmor[0] = NULL;
		equippedArmor[1] = NULL;
	}
	
	unsigned int getLevel() const;
	unsigned int getXp() const;
	int getAttack() const;
	int getDefense() const;
	int getMagic() const;
	int getSpeed() const;
	unsigned int getTotalHP() const;
	unsigned int getTotalMP() const;
	unsigned int getRemainingHP() const;
	unsigned int getRemainingMP() const;
	unsigned int getCT() const;

	bool takeDamage(unsigned int dmg);
	bool useMP(int mp);
	bool setCT(int newCT);

	void printStatus() const;
};

class PartyMember : public FightingCharacter {
	Vec2d menuLocation;

public:
	PartyMember(string d, int a, int f, int m, int s, 
							int l = 1, int h = 25, int n = 10)
							: FightingCharacter(d, a, f, m, s, l, h, n) {};
};

class Enemy : public FightingCharacter {
	int intelligence;

public:
	Enemy(string d, int a = 4, int f = 4, int m = 4, int s = 2, 
				int l = 1, int h = 10, int n = 10)
				: FightingCharacter(d, a, f, m, s, l, h, n) {};
};
