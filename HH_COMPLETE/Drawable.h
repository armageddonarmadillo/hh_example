#pragma once
#include "framework.h"

class Drawable
{
public:
	//Image and animation components
	CString path;
	CImage image;
	int srcx, srcy;
	int cc, sc, ec;
	bool loop;

	//Control components
	int durability;
	bool active, ontop, phaseable;
	int px, py, hw, hh;
	string type;

	//Required components
	int x, y, w, h;
	int xspeed, yspeed;

	//Contructor(s) / Destructor(s)
	Drawable(CString path, int x, int y);
	~Drawable();

	//Methods
	void draw(HDC context);
	void animate();
	bool collides(Drawable* t);
};