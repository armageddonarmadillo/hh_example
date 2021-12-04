#include "Box.h"

Box::Box(CString path, int x, int y, int w, int h, bool phase) : Drawable(path, x, y) {
	Box::w = w;
	Box::h = h;
	hw = w;
	hh = h;
	Box::phaseable = phase;
	durability = 999;
}

Box::~Box() {}

bool Box::side_collision(Drawable* t) {
	if (!collides(t)) {
		t->ontop = false;
		return false;
	}

	if (t->py >= y + hh && (phaseable ? false : true)) {
		t->y = y + hh + 1;
		t->yspeed = 0;
	}
	else if (t->py + t->hh <= y && (phaseable ? t->phaseable ? false : true : true)) {
		t->y = y - t->hh;
		t->yspeed = 0;
		t->ontop = true;
		return true;
	}
	else if (t->px + t->hw <= x) {
		t->x = x - t->hw - 1;
		t->xspeed = 0;
	}
	else if (t->px >= x + hw) {
		t->x = x + hw + 1;
		t->xspeed = 0;
	}

	t->ontop = false;
	return false;
}