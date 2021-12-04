#include "Nest.h"

Nest::Nest(int x, int y) /* : Drawable("IMG", x, y) */ {
	Nest::x = x;
	Nest::y = y;
}
Nest::~Nest() {}

void Nest::update(Weapon* t) {
	add_spawns();
	update_enemies(t);
	remove_enemies(t);
}

void Nest::add_spawns() {
	if (counter++ > delay) {
		if (spawns.size() < cap) spawns.add(new GroundEnemy(x, y));
		counter = 0;
	}
}

void Nest::update_enemies(Weapon* t) {
	for (GE* ge : spawns) ge->update(t);
}

void Nest::remove_enemies(Weapon* t) {
	for (GE* ge : spawns) if (!ge->active) { if (t->clipsize < 8) t->clipsize++; spawns.remove(ge); break; }
}

void Nest::draw(HDC context) {
	for (GE* ge : spawns) {
		ge->draw(context);
		ge->draw_bullets(context);
	}
}

void Nest::colliding(Box* b) {
	for (GE* ge : spawns) {
		ge->bullet_collision(b);
		b->side_collision(ge);
	}
}