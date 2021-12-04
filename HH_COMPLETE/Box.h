#pragma once
#include "Drawable.h"

class Box : public Drawable
{
public:
	bool phaseable;

	Box(CString path, int x, int y, int w, int h, bool phase);
	~Box();

	bool side_collision(Drawable* t);
};