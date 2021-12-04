#include "Clip.h"

Clip::Clip(Player* p) {
	Clip::p = p;
	max_clip = p->clipsize;
	p->clipsize = 0;
	size = 90;
}

Clip::~Clip() {}

void Clip::draw(HDC context) {
	int h = (size - 10.0) * (double)p->clipsize / max_clip;
	//make 2 brushes
	HBRUSH grey, yellow;
	//initialize the brushes
	grey = CreateSolidBrush(RGB(128, 128, 128));
	yellow = CreateSolidBrush(RGB(204, 204, 0));
	//draw bg
	SelectObject(context, grey);
	Rectangle(context, 30, 10, 40, size);

	//draw clips - this is a mathematical mess, needs refactoring for variable sizing and clipsize
	SelectObject(context, yellow);
	for (int i = 0; i < p->clipsize; i++) {
		Rectangle(context, 30 + 1, 10 + (i * 10) - 1, 30 + 1 + 8, (10 + (i * 10) - 1) + 8);
	}
	//delete brushes
	DeleteObject(grey);
	DeleteObject(yellow);
}