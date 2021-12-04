#pragma once
#include "Enemy.h"

class BossEnemy : public Enemy
{
public:
	int a_range;
	bool set;
	BossEnemy(int x, int y);
	~BossEnemy();

	void update(Weapon* t);
	void move(Weapon* t);
	void fall(Weapon* t);

	void moveright();
	void moveleft();
	void koed();
};

