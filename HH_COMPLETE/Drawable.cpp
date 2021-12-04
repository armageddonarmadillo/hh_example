#include "Drawable.h"

Drawable::Drawable(CString path, int x, int y) {
	Drawable::path = path;
	Drawable::x = x;
	Drawable::y = y;
	//DEFAULT WIDTH
	w = 64;
	hw = w;
	//DEFAULT HEIGHT
	h = 64;
	hh = h;
	srcx = 0;
	srcy = 0;
	cc = 0;
	sc = 0;
	ec = 0;
	active = true;
	loop = false;
	ontop = false;
	phaseable = false;
	durability = 100;
	type = "";
	//LOAD IMAGE LAST
	image.Load(path);
}

Drawable::~Drawable() {}

void Drawable::draw(HDC context) {
	//sets specific pink to transparent
	image.SetTransparentColor(RGB(255, 174, 201));
	//testing occlusion
	if (PLAYABLE) if (type != "player" && (x < PLAYER_X - 700 || x > PLAYER_X + 700)) return;
	//draw image to context
	else
		image.TransparentBlt(context,
			PLAYABLE ? x - mpos : x,
			y,
			w,
			h,
			srcx,
			srcy,
			w,
			h);
}

void Drawable::animate() {
	if (cc++ >= ec) cc = loop ? sc : ec;
	srcx = cc * w;
}

bool Drawable::collides(Drawable* t) {
	return (x <= t->x + t->hw &&
		x + hw >= t->x &&
		y <= t->y + t->hh &&
		y + hh >= t->y);
}