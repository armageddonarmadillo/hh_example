#include "Player.h"

Player::Player(int x, int y) : Weapon("./Pics/ViktorTesla.bmp", x, y) {
	xspeed = 0;
	yspeed = 0;
	w = 54;
	h = 42;
	hw = w;
	hh = h;
	durability = 25;
	grounded = false;
	fr = false;
	type = "player";
}

Player::~Player() {}

void Player::update() {
	move();

	//animation controller
	if (grounded || ontop) {
		if (xspeed == 0) {
			if (shooting) {
				if (fr) shootright(); else shootleft();
			}
			else {
				if (fr) idleright(); else idleleft();
			}
		}
		else {
			if (fr) moveright(); else moveleft();
		}
	}
	else {
		if (fr) jumpright(); else jumpleft();
	}

	update_bullets();
	remove_bullets();
	animate();
}

void Player::move() {
	//update previous position before applying speed: used for collisions
	px = x;
	py = y;
	//move the character
	x += xspeed;
	y += yspeed;
	//expose position to extern
	PLAYER_X = x;
	PLAYER_Y = y;
	yspeed += GRAVITY;

	if (y > GROUND - hh) {
		y = GROUND - hh;
		yspeed = 0;
		grounded = true;
	}

	if (shooting) {
		if (fr) add_bullet("./Pics/VBullet.bmp", x + w - 15, y + 10, 6, 6, P_SPEED * 1.5, 0);
		else add_bullet("./Pics/VBullet.bmp", x, y + 10, 6, 6, -P_SPEED * 1.5, 0);
	}

	if (((x - mpos < 100) || (x - mpos > 500)) && xspeed != 0) mpos += xspeed;
}


void Player::moveright() {
	w = 54;
	h = 42;
	srcy = 0;
	srcx = 54;
	ec = 8;
	sc = 1;
	loop = true;
}

void Player::moveleft() {
	w = 54;
	h = 42;
	srcy = 42;
	ec = 8;
	sc = 1;
	loop = true;
}

void Player::idleright() {
	w = 54;
	h = 42;
	srcy = 0;
	srcx = 0;
	ec = 0;
	sc = 0;
	loop = false;
}

void Player::idleleft() {
	w = 54;
	h = 42;
	srcy = 42;
	srcx = 0;
	ec = 0;
	sc = 0;
	loop = false;
}

void Player::jumpright() {
	w = 48;
	h = 56;
	srcy = 86;
	ec = 5;
	sc = 0;
	loop = false;
}

void Player::jumpleft() {
	w = 48;
	h = 56;
	srcy = 146;
	ec = 5;
	sc = 0;
	loop = false;
}

void Player::shootright() {
	w = 60;
	h = 38;
	srcy = 199;
	ec = 0;
	sc = 0;
	loop = false;
}

void Player::shootleft() {
	w = 60;
	h = 38;
	srcy = 237;
	ec = 0;
	sc = 0;
	loop = false;
}
