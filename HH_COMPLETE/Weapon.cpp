#include "Weapon.h"

Weapon::Weapon(CString path, int x, int y) : Drawable(path, x, y) {}

Weapon::~Weapon() {}

void Weapon::update(Drawable* t) {
	update_bullets();
	bullet_collision(t);
	remove_bullets();
}

void Weapon::add_bullet(CString path, int x, int y, int w, int h, int xs, int ys) {
	if (bullets.size() > clipsize) return;
	bullets.add(new Bullet(path, x, y, w, h, xs, ys));
}

void Weapon::add_bullet(CString path, int x, int y, int w, int h, int xs, int ys, bool fireball) {
	if (!fireball) return;

	if (bullets.size() > clipsize) return;
	Bullet* b = new Bullet(path, x, y, w, h, xs, ys);
	b->srcx = 0;
	b->srcy = 47;
	bullets.add(b);
}

void Weapon::bullet_collision(Drawable* t) {
	for (Bullet* b : bullets) if (b->collides(t)) {
		b->active = false;
		t->durability--;
	}
}

void Weapon::update_bullets() {
	for (Bullet* b : bullets) b->update();
}

void Weapon::remove_bullets() {
	for (Bullet* b : bullets) if (!b->active) { bullets.remove(b); break; }
}

void Weapon::draw_bullets(HDC context) {
	for (Bullet* b : bullets) b->draw(context);
}
