#pragma once
#include "framework.h"

struct Rec {
	int top, left, bottom, right;
};

struct Cell {
	Rec rec[4];
};

struct Point {
	int x, y;
};

class Grid
{
public:
	list<Cell> cells;
	int cw, ch;	//cell X Y W H
	int ix = 0, iy = 0, sw, sh; //intial X Y screen W H
	bool active;
	Point last;

	Grid(int w, int h, int cw, int ch);
	~Grid();

	void draw(HDC context);
	void load_grid();
	bool edit_grid(Cell c);

	Cell click(int x, int y);
	Rec rect(int l, int t, int r, int b);
	Cell cellmaker(Rec L, Rec T, Rec R, Rec B);
};
