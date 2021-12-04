#pragma once
#include "framework.h"

class Button
{
public:
	int x, y, w, h;
	COLORREF color;
	COLORREF def_color;
	string type;
	LPCWSTR text;
	Button(string type, LPCWSTR text, COLORREF color, int x, int y, int w, int h);
	~Button() {
		delete& x;
		delete& y;
		delete& w;
		delete& h;
		delete& color;
	}

	void draw(HDC context);
	bool click(int x, int y);
};

