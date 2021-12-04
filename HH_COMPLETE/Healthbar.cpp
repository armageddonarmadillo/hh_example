#include "Healthbar.h"

Healthbar::Healthbar(Player* p) {
	Healthbar::p = p;
	max_hp = p->durability;
	size = 90;
}

Healthbar::~Healthbar() {}

void Healthbar::draw(HDC context) {
	int h = (size - 10) * (double)p->durability / max_hp;

	//make 2 brushes
	HBRUSH red, green;
	//initialize the brushes
	red = CreateSolidBrush(RGB(200, 50, 50));
	green = CreateSolidBrush(RGB(50, 200, 50));
	//draw red bar
	SelectObject(context, red);
	Rectangle(context, 10, 10, 20, size);
	//draw green bar
	if (p->durability >= 0) {
		SelectObject(context, green);
		Rectangle(context, 10, size - h, 20, size);
	}
	//delete brushes
	DeleteObject(red);
	DeleteObject(green);

}