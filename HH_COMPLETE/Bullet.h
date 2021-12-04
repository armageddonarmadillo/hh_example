#pragma once
#include "Drawable.h"

class Bullet : public Drawable
{
public:
	int dt, md; //Distance travelled, maximum distance

	Bullet(CString path, int x, int y, int w, int h, int xs, int ys);
	~Bullet();

	void update();
};

