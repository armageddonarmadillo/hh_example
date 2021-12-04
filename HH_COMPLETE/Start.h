#pragma once
#include "Scene.h"
#include "Button.h"

class Start : public Scene
{
public:
	list<Button*> buttons;

	Start();
	~Start();

	void draw(HDC context);
	Button* update(int x, int y);
	void highlight(int x, int y, COLORREF color);
};

