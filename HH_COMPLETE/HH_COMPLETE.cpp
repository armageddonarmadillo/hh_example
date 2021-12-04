// HH_COMPLETE.cpp : Defines the entry point for the application.
//
#include "HH_COMPLETE.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//	Game Variables
CString level = "./Levels/aa_lvl.txt";
int mpos = 0;
int PLAYER_X = 0;
int PLAYER_Y = 0;
int temp_mpos = mpos;
bool PLAYABLE = true;
bool started = false,
paused = false,
end = false,
win = false,
gridded = false,
pathfindermode = false;
HDC buffer_context;

//	Game Objects
Player* mc;
Healthbar* life;
Clip* clip;
Grid* grid;
Background* bg;
Background* ground;
Background* start = new Background("./Pics/TitleScreen.jpg", 0, 0, 700, 550, 1);
Background* gameover = new Background("./Pics/gameover.png", 0, 0, 700, 550, 1);
Background* pause = new Background("./Pics/Pause.jpg", 0, 0, 700, 550, 1);
Start* start_scene = new Start();

//	Game Collections
static list<Nest*> nest_list;
static list<Box*> box_list;
static list<Drawable*> generic_list;
static list<Enemy*> special_enemy_list;

//	Editor Variables
static string placeables[] = { "[S]", "[C]", "[X]", "[N]", "[G]", "[F]", "[B]" };
static int placeable_index = 0;
static string placeable = placeables[placeable_index];

//	Game forward declarations
bool create_by_id(string s,
	int x,
	int y,
	int w = gcellw,
	int h = gcellh,
	bool p = false
);
void add_element(string s, int x, int y);
void remove_element(string s, int x, int y);
list<list<string>>	loadLevel(CString lvl);
void				createLevel(list<list<string>> lvl);
void				startLevel(CString lvl);
void				buffer_setup();
void				draw(HWND w);
void				start_grid(int grid_size, int grid_height, int cell_width, int cell_height);
void				clear_lists();

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_HHCOMPLETE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HHCOMPLETE));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HHCOMPLETE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_HHCOMPLETE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 700, 550, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	SetTimer(hWnd, 1, 17, NULL);
	buffer_setup();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_KEYDOWN:
	{
		if (!started) break;
		switch (wParam) {
		/*A*/case 0x41:
			mc->xspeed = -P_SPEED;
			mc->fr = false;
			break;
		/*D*/case 0x44:
			mc->xspeed = P_SPEED;
			mc->fr = true;
			break;
		/*S*/case 0x53:
			mc->phaseable = true;
			break;
		/*W*/case 0x57:
			if (mc->grounded || mc->ontop) {
				mc->yspeed = -P_SPEED * 1.5;
				mc->grounded = false;
			}
			break;
		/*SPACE*/case VK_SPACE:
			mc->shooting = true;
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam) {
		/*ENTER*/case VK_RETURN:
			if (end && started) {
				clear_lists();
				started = false;
				end = false;
				gridded = false;
				break;
			}
			else if (!started) {
				clear_lists();
				started = true;
				startLevel(level);
				break;
			}
			else if (pathfindermode) {
				clear_lists();
			}
			break;
		case VK_ESCAPE:
			started = false;
			paused = false;
			end = false;
			win = false;
			gridded = false;
			break;
		/*A*/case 0x41:
			if (!started) break;
			mc->xspeed = 0;
			mc->fr = false;
			break;
		/*D*/case 0x44:
			if (!started) break;
			mc->xspeed = 0;
			mc->fr = true;
			break;
		/*P*/case 0x50:
			if (!started) break;
			paused = !paused;
			if (paused) {
				temp_mpos = mpos; mpos = 0;
			}
			else mpos = temp_mpos;
			break;
		/*S*/case 0x53:
			if (!started) break;
			mc->phaseable = false;
			break;
		/*SPACE*/case VK_SPACE:
			if (!started) break;
			mc->shooting = false;
			break;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT point;
		if (GetCursorPos(&point))
			if (!ScreenToClient(hWnd, &point))
				break;
		if (!started) start_scene->highlight(point.x, point.y, RGB(15, 255, 15));
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINT point;
		if (GetCursorPos(&point))
			if (!ScreenToClient(hWnd, &point))
				break;
		if (!started) start_scene->highlight(point.x, point.y, RGB(60, 225, 60));
	}
	break;
	case WM_LBUTTONUP:
	{
		POINT point;
		if (GetCursorPos(&point))
			if (!ScreenToClient(hWnd, &point))
				break;
		if (!started) {
			start_scene->highlight(point.x, point.y, RGB(55, 155, 55));
			if (start_scene->update(point.x, point.y)->type == "start") {
				clear_lists();
				special_enemy_list.add(new BossEnemy(-500, GROUND - 99));
				started = true;
				gridded = false;
				startLevel(level);
			}
			else if (start_scene->update(point.x, point.y)->type == "editor") {
				clear_lists();
				started = true;
				gridded = true;
				startLevel(level);
			}
			else if (start_scene->update(point.x, point.y)->type == "pathfinder") {
				pathfindermode = true;
				PLAYABLE = false;
				started = true;
				start_grid(700, 450, gcellw, gcellh);
			}
			else if (start_scene->update(point.x, point.y)->type == "exit") {
				PostMessage(hWnd, WM_DESTROY, 0, 0);
			}
			break;
		}
		//ADDITION OF SELECTED ELEMENT
		if (!started) break;
		if (gridded && grid->edit_grid(grid->click(mpos + point.x, point.y)) && PLAYABLE)
			add_element(placeable, grid->last.x, grid->last.y);
		if (gridded && grid->edit_grid(grid->click(point.x, point.y)) && !PLAYABLE)
			add_element(placeable, grid->last.x, grid->last.y);
	}
	break;
	case WM_RBUTTONUP:
	{
		if (!started) break;
		//REMOVAL OF CLICKED ELEMENT
		POINT point;
		if (GetCursorPos(&point))
			if (ScreenToClient(hWnd, &point))
				if (gridded && grid->edit_grid(grid->click(mpos + point.x, point.y)))
					remove_element(placeable, grid->last.x, grid->last.y);
	}
	break;
	case WM_MOUSEWHEEL:
	{
		if (!started && !gridded) break;
		if (GET_WHEEL_DELTA_WPARAM(wParam) == 120) {
			if (++placeable_index > sizeof(placeables) / sizeof(placeables[0]) - 1) placeable_index = 0;
			placeable = placeables[placeable_index];
		}
		else {
			if (--placeable_index < 0) placeable_index = sizeof(placeables) / sizeof(placeables[0]) - 1;
			placeable = placeables[placeable_index];
		}
	}
	break;
	case WM_TIMER:
	{
		if (started && !end && !paused && PLAYABLE) {
			//Player Logic
			mc->update();
			for (Drawable* generic : generic_list) {
				if (generic->type == "goal" && mc->collides(generic))
					win = true;
			}
			for (Enemy* e : special_enemy_list) e->update(mc);
			for (Nest* nest : nest_list) nest->update(mc);
			for (Box* box : box_list) if (box->side_collision(mc)) break;
			for (Box* box : box_list) {
				mc->bullet_collision(box);
			}

			//Nest Logic
			for (Nest* nest : nest_list)
				for (Box* b : box_list)
					nest->colliding(b);

			if (mc->durability <= 0) { mpos = 0; end = true; }

		}
		PostMessage(hWnd, WM_PAINT, 0, 0);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		if (started && !end && !paused && !win && PLAYABLE) {
			bg->draw(buffer_context);
			ground->draw(buffer_context);
			for (Nest* nest : nest_list) nest->draw(buffer_context);
			for (Enemy* e : special_enemy_list) {
				if (e->ko) continue;
				e->draw(buffer_context);
				e->draw_bullets(buffer_context);
			}
			for (Drawable* generic : generic_list) { generic->animate(); generic->draw(buffer_context); }
			if (grid != NULL) grid->draw(buffer_context);
			for (Box* box : box_list) box->draw(buffer_context);
			mc->draw(buffer_context);
			mc->draw_bullets(buffer_context);
			life->draw(buffer_context);
			clip->draw(buffer_context);
		}
		if (!started && PLAYABLE) start_scene->draw(buffer_context);//start->draw(buffer_context);
		if (paused) pause->draw(buffer_context);
		if (end) gameover->draw(buffer_context);
		if (pathfindermode) {
			HBRUSH bg_color = CreateSolidBrush(RGB(102, 221, 170));
			RECT rect = { 0, 0, GAMEWIDTH, GAMEHEIGHT };
			LPCWSTR text = L"HAUNTED HARBOUR";
			SelectObject(buffer_context, bg_color);
			Rectangle(buffer_context, rect.left, rect.top, rect.right, rect.bottom);
			if (grid != NULL) grid->draw(buffer_context);
			for (Box* box : box_list) box->draw(buffer_context);
			DBOUT(sizeof(box_list));
		}
		draw(hWnd);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

list<list<string>> loadLevel(CString lvl) {
	std::ifstream file(lvl);
	string str;
	list<string> lines;
	list < list<string>> level;

	while (std::getline(file, str)) lines.add(str);

	string delim = "|";
	list<string> elements;
	size_t pos = 0;
	for (string s : lines) {
		while ((pos = s.find(delim)) != string::npos) {
			elements.add(s.substr(0, pos));
			s.erase(0, pos + delim.length());
		}
		level.add(elements);
		elements.clear();
	}

	return level;
}

void createLevel(list<list<string>> lvl) {
	int cw = gcellw;	//game cell width
	int ch = gcellh;	//game cell height
	int r = 0, c = 0;	//row/column in level

	for (list<string> line : lvl) {
		for (string s : line) {
			add_element(s, c * cw, r * ch);
			/*END*/ if (c++ == line.size() - 1) c = 0;
		}
		/*END*/ if (r++ == lvl.size() - 1) r = 0;
	}

	//set up background and ground
	bg = new Background("./Pics/Background3.jpg", 0, 0, 5118, 800, 0.2);
	ground = new Background("./Pics/Ground.bmp", 0, GROUND, 774, 128, 1);
}

void startLevel(CString lvl) {
	createLevel(loadLevel(lvl));
}

void buffer_setup() {
	HDC context;
	HBITMAP buffer;
	context = GetDC(0);
	buffer_context = CreateCompatibleDC(context);
	buffer = CreateCompatibleBitmap(context, 800, 600);
	SelectObject(buffer_context, buffer);
	ReleaseDC(0, context);
}

void draw(HWND w) {
	HDC context = GetDC(w);
	TransparentBlt(
		context, 0, 0, 700, 550,
		buffer_context, 0, 0, 700, 550,
		RGB(255, 174, 201)
	);
	DeleteDC(context);
}

void start_grid(int grid_size, int grid_height, int cell_width, int cell_height) {
	grid = new Grid(grid_size, grid_height, cell_width, cell_height);
}

bool create_by_id(string s,
	int x,
	int y,
	int w,
	int h,
	bool p
) {
	if (s == "[C]") {
		box_list.add(new Box("./Pics/Crate.bmp", x, y, w, h, p));
		return true;
	}
	if (s == "[S]") {
		box_list.add(new Box("./Pics/SmallCrate.bmp", x, y, w, h, p));
		return true;
	}
	if (s == "[N]") {
		nest_list.add(new Nest(x, y));
		return true;
	}
	if (s == "[F]") {
		special_enemy_list.add(new FlyingEnemy(x, y));
		return true;
	}
	if (s == "[B]") {
		special_enemy_list.add(new BossEnemy(x, y + 99 > GROUND ? GROUND - 99 : y));
		return true;
	}
	if (s == "[P]") {
		mc = new Player(x, y);
		life = new Healthbar(mc);
		clip = new Clip(mc);
		mpos = mc->x - 96;
		return true;
	}
	if (s == "[G]") {
		Drawable* goal = new Drawable("./Pics/crystal.png", x, y);
		goal->type = "goal";
		goal->ec = 8;
		goal->sc = 0;
		goal->loop = true;
		generic_list.add(goal);
		return true;
	}
	return false;
}

void add_element(string s, int x, int y) {
	if (s == "[C]") create_by_id(s, x, y, gcellw * 2, gcellh * 2, false);
	if (s == "[S]") create_by_id(s, x, y, gcellw, gcellh, true);
	if (s == "[P]" || s == "[N]" || s == "[G]" || s == "[F]" || s == "[B]") create_by_id(s, x, y);
}

void remove_element(string s, int x, int y) {
	if (s == "[C]") for (Box* b : box_list) if (b->x == x && b->y == y) { box_list.remove(b); break; }
	if (s == "[S]") for (Box* b : box_list) if (b->x == x && b->y == y) { box_list.remove(b); break; }
	if (s == "[N]") for (Nest* n : nest_list) if (n->x == x && n->y == y) { nest_list.remove(n); break; }
	if (s == "[F]" || s == "[B]") for (Enemy* n : special_enemy_list) if (n->x == x && n->y == y) { special_enemy_list.remove(n); break; }
}

void clear_lists() {
	nest_list.clear();
	box_list.clear();
	generic_list.clear();
	special_enemy_list.clear();
}