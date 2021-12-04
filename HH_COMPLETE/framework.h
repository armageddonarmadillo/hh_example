// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <atlimage.h>
#include <atlstr.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include <list>
#include <algorithm>
#include <ostream>
#include <fstream>
#include <string>
extern int mpos;
extern int PLAYER_X;
extern int PLAYER_Y;
extern bool PLAYABLE;
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define GRAVITY 2
#define GROUND 450
#define add push_back
#define P_SPEED 15
#define GE_SPEED 3
#define list std::list
#define string std::string
#define gscale 1
#define gcellw 32
#define gcellh 32
#define GAMEWIDTH 700
#define GAMEHEIGHT 550
#define BTNWIDTH 125
#define BTNHEIGHT 50
#define DBOUT( s ) {					\
	std::wostringstream o;				\
	o << s;								\
	OutputDebugStringW(o.str().c_str());\
}