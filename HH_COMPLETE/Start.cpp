#include "Start.h"

Start::Start() : Scene(0, 0, GAMEWIDTH, GAMEHEIGHT) {
	buttons.add(new Button(
		"start", L"Start", RGB(55, 200, 55),
		GAMEWIDTH / 2 - BTNWIDTH / 2, (int)buttons.size() * (BTNHEIGHT + 25) + GAMEHEIGHT / 3 - BTNHEIGHT, BTNWIDTH, BTNHEIGHT
	));
	buttons.add(new Button(
		"editor", L"Level Editor", RGB(55, 200, 55),
		GAMEWIDTH / 2 - BTNWIDTH / 2, (int)buttons.size() * (BTNHEIGHT + 25) + GAMEHEIGHT / 3 - BTNHEIGHT, BTNWIDTH, BTNHEIGHT
	));
	buttons.add(new Button(
		"pathfinder", L"Pathfinder", RGB(55, 200, 55),
		GAMEWIDTH / 2 - BTNWIDTH / 2, (int)buttons.size() * (BTNHEIGHT + 25) + GAMEHEIGHT / 3 - BTNHEIGHT, BTNWIDTH, BTNHEIGHT
	));
	buttons.add(new Button(
		"exit", L"Exit", RGB(55, 200, 55),
		GAMEWIDTH / 2 - BTNWIDTH / 2, (int)buttons.size() * (BTNHEIGHT + 25) + GAMEHEIGHT / 3 - BTNHEIGHT, BTNWIDTH, BTNHEIGHT
	));
}

void Start::draw(HDC context) {
	HBRUSH bg_color = CreateSolidBrush(RGB(102, 221, 170));
	RECT rect = { 0, 0, GAMEWIDTH, GAMEHEIGHT };
	LPCWSTR text = L"HAUNTED HARBOUR";
	SelectObject(context, bg_color);
	Rectangle(context, rect.left, rect.top, rect.right, rect.bottom);
	for (Button* b : buttons) b->draw(context);

	rect.left = 285;
	rect.top = y + h / 7;
	SetTextColor(context, RGB(200, 50, 200)); //RRGGBBAA
	SetBkMode(context, TRANSPARENT);
	DrawText(context, text, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
	SetTextColor(context, RGB(0, 0, 0)); // change color back
	DeleteObject(bg_color);
	DeleteObject(&rect);
	DeleteObject(&text);
}

Button* Start::update(int x, int y) {
	for (Button* b : buttons)
		if (b->click(x, y))  return b;
}

void Start::highlight(int x, int y, COLORREF color) {
	for (Button* b : buttons)
		if (b->click(x, y)) b->color = color;
		else b->color = b->def_color;
}