#include "BossEnemy.h"

BossEnemy::BossEnemy(int x, int y) : Enemy("./Pics/HungrySailor.bmp", x, y) {
	a_range = 200;
	w = 78;
	h = 99;
	hw = w;
	hh = h;
	durability = 25;
	ko = false;
	fr = false;
	drop = false;
	set = false;
	clipsize = 1;
}

BossEnemy::~BossEnemy() {}

void BossEnemy::update(Weapon* t) {
	move(t);
	fall(t);
	ko = durability <= 0;

	if (!ko)
		if (fr) moveright(); else moveleft();
	else koed();

	Weapon::update(t);
	if (!ko) t->bullet_collision(this);
	animate();
}

void BossEnemy::move(Weapon* t) {
	if (ko) return;

	if (x - a_range < t->x && t->x < x + a_range) {
		double xdist = abs(x - t->x);
		double ydist = abs(y - t->y);

		int dx = 1;
		int dy = 1;

		if (t->x < x) dx = -1;
		if (t->y < y) dy = -1;

		if (xdist > ydist) add_bullet("./Pics/Fireballs.bmp", x, y, 34, 31, 10 * dx, 10 * ydist / xdist * dy, true);
		else add_bullet("./Pics/Fireballs.bmp", x, y, 34, 31, 10 * xdist / ydist * dx, 10 * dy, true);
	}
}

void BossEnemy::fall(Weapon* t) {

}

void BossEnemy::moveright() {

}

void BossEnemy::moveleft() {
	srcx = 0;
	if (cc >= ec) set = !set;
	srcy = set ? h : 0;
	ec = 8;
	sc = 0;
	loop = true;
}

void BossEnemy::koed() {

}
