#include "FlyingEnemy.h"
FlyingEnemy::FlyingEnemy(int x, int y) : Enemy("./Pics/SeaHag.bmp", x, y)
{
	w = 28;
	h = 39;
	hw = w;
	hh = h;
	durability = 3;
	ko = false;
	fr = false;
	drop = false;
	clipsize = 1;
	radius = 20; //THIS MAKES THE CIRCLE BIGGER
	angle = 0;
	cx = x;
	cy = y;
}

FlyingEnemy::~FlyingEnemy() {}

void FlyingEnemy::update(Weapon* t) {
	move(t);
	fall(t);
	ko = durability <= 0;

	if (!ko) {
		if (fr) moveright(); else moveleft();
	}
	else {
		koed();
	}

	Weapon::update(t);
	if (!ko) t->bullet_collision(this);
	animate();
}

void FlyingEnemy::move(Weapon* t) {
	if (ko) return;

	double radians = (double)angle / 180 * 3.14159;
	x = cx + radius * cos(radians);
	y = cy + radius * sin(radians);

	if (t->x + t->w > x) { angle += 10; fr = true; }
	else if (t->x < x + w) { angle -= 10; fr = false; }

	if (x - 250 < t->x && t->x < x + 250) {
		double xdist = abs(x - t->x);
		double ydist = abs(y - t->y);

		int dx = 1;
		int dy = 1;

		if (t->x < x) dx = -1;
		if (t->y < y) dy = -1;

		if (xdist > ydist) add_bullet("./Pics/GreenFire.bmp", x, y, 6, 6, 10 * dx, 10 * ydist / xdist * dy);
		else add_bullet("./Pics/GreenFire.bmp", x, y, 6, 6, 10 * xdist / ydist * dx, 10 * dy);
	}

}

void FlyingEnemy::fall(Weapon* t) {
	if (!ko) return;
	y += yspeed;
	yspeed += GRAVITY;
	active = y < 650;
}

void FlyingEnemy::moveright() {
	srcx = 0;
	srcy = 40;
	ec = 3;
	sc = 0;
	loop = true;
}

void FlyingEnemy::moveleft() {
	srcx = 0;
	srcy = 0;
	ec = 3;
	sc = 0;
	loop = true;
}

void FlyingEnemy::koed() {
	srcx = 0;
	srcy = 156;
	w = 32;
	h = 32;
	ec = 6;
	sc = 0;
	loop = true;
}