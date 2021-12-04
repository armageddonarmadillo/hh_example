#pragma once
#include "Drawable.h"
#include "Weapon.h"
#include "Enemy.h"
#include "GroundEnemy.h"
#include "Box.h"

#define GE Enemy

class Nest // : public Drawable if theres a visual asset
{
public:
	/*Remove if theres a a visual */ int x, y, w, h;
	int counter = 250, delay = 250, cap = 50; //spawn timer, spawn limit

	list<GE*> spawns;

	Nest(int x, int y);
	~Nest();

	void update(Weapon* t);
	void add_spawns();
	void update_enemies(Weapon* t);
	void remove_enemies(Weapon* t);
	void colliding(Box* b);
	void draw(HDC context);
};

