#include "Grid.h"

Grid::Grid(int w, int h, int cw, int ch) {
	Grid::sw = w;
	Grid::sh = h;
	Grid::cw = cw;
	Grid::ch = ch;
	active = true;
	load_grid();
}

Grid::~Grid() {}

void Grid::draw(HDC context) {
	//create brush
	HBRUSH color = CreateSolidBrush(RGB(255, 50, 50));
	//pair context to brush
	SelectObject(context, color);
	//draw
	for (Cell c : cells) {
		if (PLAYABLE) if (c.rec[0].left < PLAYER_X - 256 ||
			c.rec[0].right > PLAYER_X + 256) continue;
		for (int i = 0; i < 4; i++) {
			Rectangle(context,
				PLAYABLE ? c.rec[i].left - mpos : c.rec[i].left,
				c.rec[i].top,
				PLAYABLE ? c.rec[i].right - mpos : c.rec[i].right,
				c.rec[i].bottom
			);
		}
	}
	//pop brush
	DeleteObject(color);
}

Cell Grid::click(int x, int y) {
	for (Cell c : cells) {
		if (c.rec[0].left < x &&
			c.rec[2].right > x &&
			c.rec[1].top < y &&
			c.rec[3].bottom > y) {
			return c;
		}
	}
}

void Grid::load_grid() {
	int w_cells = sw / cw;
	int h_cells = sh / ch;
	for (int y = 0; y < h_cells; y++) {
		for (int x = 0; x < w_cells; x++) {
			cells.add(
				cellmaker(
					rect((x * cw), y * ch, (x * cw + cw), y * ch + 1),
					rect((x * cw), y * ch, (x * cw + 1), y * ch + ch),
					rect((x * cw + cw), y * ch, (x * cw + cw + 1), y * ch + ch),
					rect((x * cw), y * ch + ch, (x * cw + cw), y * ch + ch + 1)
				));
		}
	}
}

bool Grid::edit_grid(Cell c) {
	for (Cell cell : cells) {
		if (cell.rec[0].left == c.rec[0].left &&
			cell.rec[0].top == c.rec[0].top &&
			cell.rec[0].right == c.rec[0].right &&
			cell.rec[0].bottom == c.rec[0].bottom
			) {
			last.x = c.rec[0].left;
			last.y = c.rec[0].top;
			return true;
		}
	}
	return false;
}

Rec Grid::rect(int l, int t, int r, int b) {
	Rec rec;
	rec.top = t;
	rec.left = l;
	rec.bottom = b;
	rec.right = r;
	return rec;
}

Cell Grid::cellmaker(Rec L, Rec T, Rec R, Rec B) {
	Cell cell;
	cell.rec[0] = L;
	cell.rec[1] = T;
	cell.rec[2] = R;
	cell.rec[3] = B;
	return cell;
}