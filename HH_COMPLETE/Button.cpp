#include "Button.h"

Button::Button(string type, LPCWSTR text, COLORREF color, int x, int y, int w, int h) {
	Button::x = x;
	Button::y = y;
	Button::w = w;
	Button::h = h;
	Button::text = text;
	Button::def_color = color;
	Button::color = def_color;
	Button::type = type;
}

void Button::draw(HDC context) {
	HBRUSH brush = CreateSolidBrush(color);
	RECT rect = { x, y, x + w, y + h };
	SelectObject(context, brush);
	Rectangle(context, rect.left, rect.top, rect.right, rect.bottom);

	rect.left = x + w / 3;
	rect.top = y + h / 3;
	//SetTextColor(context, 0x00000000); //RRGGBBAA
	SetBkMode(context, TRANSPARENT);
	DrawText(context, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);

	DeleteObject(brush);
	DeleteObject(&rect);
}

bool Button::click(int x, int y) {
	return (
		Button::x < x &&
		Button::x + w > x &&
		Button::y < y &&
		Button::y + h > y
		);
}
