#pragma once
#include "Enemy.h"

class FlyingEnemy : public Enemy
{
public:
	int radius, angle, cx, cy;
	FlyingEnemy(int x, int y);
	~FlyingEnemy();

	void update(Weapon* t);
	void move(Weapon* t);
	void fall(Weapon* t);

	void moveright();
	void moveleft();
	void koed();
};

