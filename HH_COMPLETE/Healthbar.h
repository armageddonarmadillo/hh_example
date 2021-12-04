#pragma once
#include "Player.h"

class Healthbar
{
public:
	Player* p;
	int max_hp, cur_hp, size;

	Healthbar(Player* p);
	~Healthbar();

	void draw(HDC context);
};

