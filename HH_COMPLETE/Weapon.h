#pragma once
#include "Drawable.h"
#include "Bullet.h"

class Weapon : public Drawable
{
public:
	int clipsize;
	list<Bullet* > bullets;

	Weapon(CString path, int x, int y);
	~Weapon();

	void update(Drawable* t);
	void add_bullet(CString path, int x, int y, int w, int h, int xs, int ys);
	void add_bullet(CString path, int x, int y, int w, int h, int xs, int ys, bool fireball);
	void bullet_collision(Drawable* t);
	void update_bullets();
	void remove_bullets();
	void draw_bullets(HDC context);
};

