#pragma once
#include "Enemy.h"

#define RANGE 250 //target search range

class GroundEnemy : public Enemy
{
public:
	int counter = 0, delay = 25; //timer for enemy firing

	GroundEnemy(int x, int y);
	~GroundEnemy();

	void update(Weapon* t);
	void fall(Weapon* t);
	void move(Weapon* t);

	void moveright();
	void moveleft();
	void ko_right();
	void ko_left();
	void idle_right();
	void idle_left();
};