#include "Background.h"

Background::Background(CString path, int x, int y, int w, int h, double ss) : Drawable(path, x, y) {
	Background::w = w;
	Background::h = h;
	Background::ss = ss;
}

Background::~Background() {}

void Background::draw(HDC context) {
	int rx /* RELATIVE X TO PLAYER */ = (int)((x - mpos) * ss) % w;

	//set certain pink to transparent
	image.SetTransparentColor(RGB(255, 174, 201));

	//draw in relation to player
	image.TransparentBlt(context,
		rx,
		y,
		w,
		h,
		0,
		0,
		w,
		h);

	image.TransparentBlt(context,
		rx + w,
		y,
		w,
		h,
		0,
		0,
		w,
		h);

	image.TransparentBlt(context,
		rx - w,
		y,
		w,
		h,
		0,
		0,
		w,
		h);
}