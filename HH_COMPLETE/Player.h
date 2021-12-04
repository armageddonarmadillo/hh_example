#pragma once
#include "Weapon.h"

class Player : public Weapon
{
public:
	bool grounded, shooting, fr; //animation variables

	Player(int x, int y);
	~Player();

	void update();
	void move();

	//animation state methods
	void moveright();
	void moveleft();
	void idleright();
	void idleleft();
	void jumpright();
	void jumpleft();
	void shootright();
	void shootleft();
};

