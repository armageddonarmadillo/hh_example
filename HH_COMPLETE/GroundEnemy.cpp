#include "GroundEnemy.h"

GroundEnemy::GroundEnemy(int x, int y) : Enemy("./Pics/SkullCrab.bmp", x, y) {
	w = 28;
	h = 37;
	hw = w;
	hh = h;
	durability = 5;
	ko = false;
	drop = false;
	fr = false;
}

GroundEnemy::~GroundEnemy() {}

void GroundEnemy::update(Weapon* t) {
	ko = durability <= 0;
	move(t);
	fall(t);

	if (!ko) {
		if (xspeed == 0) {
			if (fr) idle_right(); else idle_left();
		}
		else {
			if (fr) moveright(); else moveleft();
		}
	}
	else {
		if (fr) ko_right(); else ko_left();
	}

	update_bullets();
	bullet_collision(t);
	remove_bullets();
	if (!ko) t->bullet_collision(this);	//also checks for collision from target, optional
	animate();
}

void GroundEnemy::fall(Weapon* t) {
	if (!ko) return;

	if (!drop) {
		if (collides(t)) {
			yspeed -= 15;
			xspeed = (x - t->x != 0 ? (x - t->x) / abs(x - t->x) : -1) * GE_SPEED;
			drop = true;
		}
	}
	else {
		x += xspeed;
		y += yspeed;
		yspeed += GRAVITY;
	}

	active = y < 650;
}

void GroundEnemy::move(Weapon* t) {
	if (ko) return;
	bool t_in_range = t->x > x - RANGE && t->x < x + RANGE;
	int direction = 1;
	px = x;
	py = y;
	if (t_in_range) {
		direction = t->x - x != 0 ? (t->x - x) / abs(t->x - x) : -1;
		if (counter++ > delay) {
			add_bullet("./Pics/GreenFire.bmp", x, y, 6, 6, direction * GE_SPEED * 3, 0);
		}
	}
	xspeed = direction * GE_SPEED;
	x += xspeed;
	y += yspeed;
	yspeed += GRAVITY;

	if (y > GROUND - hh) {
		y = GROUND - hh;
		yspeed = 0;
	}

	if (xspeed > 0) fr = true; else if (xspeed < 0) fr = false;
}

void GroundEnemy::moveright() {
	srcy = 37;
	srcx = 28;
	sc = 1;
	ec = 9;
	loop = true;
}

void GroundEnemy::moveleft() {
	srcy = 0;
	srcx = 28;
	sc = 1;
	ec = 9;
	loop = true;
}

void GroundEnemy::ko_right() {
	srcy = 107;
	srcx = 0;
	sc = 0;
	ec = 0;
	loop = false;
}

void GroundEnemy::ko_left() {
	srcy = 73;
	srcx = 0;
	sc = 0;
	ec = 0;
	loop = false;
}

void GroundEnemy::idle_right() {
	srcy = 37;
	srcx = 0;
	sc = 0;
	ec = 0;
	loop = false;
}

void GroundEnemy::idle_left() {
	srcy = 0;
	srcx = 0;
	sc = 0;
	ec = 0;
	loop = false;
}
