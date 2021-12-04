#pragma once
#include "Weapon.h"

class Enemy : public Weapon
{
public:
	bool ko, fr, drop; //animation variables

	Enemy(CString path, int x, int y) : Weapon(path, x, y) {}
	~Enemy() {}

	virtual void update(Weapon* t) = 0;
	virtual void move(Weapon* t) = 0;
	virtual void fall(Weapon* t) = 0;
};

