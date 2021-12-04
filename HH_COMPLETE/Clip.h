#pragma once
#include "Player.h"

class Clip
{
public:
	Player* p;
	int max_clip = 15, clipsize, size;

	Clip(Player* p);
	~Clip();

	void draw(HDC context);
};

