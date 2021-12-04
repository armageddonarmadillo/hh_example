#include "Bullet.h"

Bullet::Bullet(CString path, int x, int y, int w, int h, int xs, int ys) : Drawable(path, x, y) {
	Bullet::w = w;
	Bullet::h = h;
	Bullet::hw = w;
	Bullet::hh = h;
	Bullet::xspeed = xs;
	Bullet::yspeed = ys;
	dt = 0;
	md = 350; // maximum distance a bullet can travel
}

Bullet::~Bullet() {}

void Bullet::update() {
	px = x;
	py = y;
	x += xspeed;
	y += yspeed;

	dt += abs(xspeed) + abs(yspeed);

	if (dt > md) {
		dt = 0;
		active = false;
	}
}