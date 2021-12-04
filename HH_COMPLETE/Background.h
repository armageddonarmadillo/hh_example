#pragma once
#include "Drawable.h"

class Background : public Drawable
{
public:
	double ss;	//scrollspeed

	Background(CString path, int x, int y, int w, int h, double ss);
	~Background();
	void draw(HDC context);
};

