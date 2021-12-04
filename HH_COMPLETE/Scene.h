#pragma once
#include "Drawable.h"
#include "Weapon.h"

class Scene
{
public:
	list<Drawable*> elements;
	int x, y, w, h; // position and size of this scene

	Scene(int x, int y, int w, int h) {
		Scene::x = x;
		Scene::y = y;
		Scene::w = w;
		Scene::h = h;
	}
	~Scene() { delete& elements; }

	virtual void draw(HDC context) = 0;
	//virtual void update(Weapon* t = NULL) = 0;
};

