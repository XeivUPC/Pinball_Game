#pragma once

#include "raylib.h"

#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )

#define PIXEL_X_METER 16.f
#define METERS_X_PIXEL 1.f/PIXEL_X_METER

#define METERS_TO_PIXELS(m) (int)(PIXEL_X_METER * (m))
#define PIXELS_TO_METERS(p) (METERS_X_PIXEL * (p))

typedef unsigned int uint;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef unsigned char uchar;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH		  160
#define SCREEN_HEIGHT		  144
#define SCREEN_SIZE				4
#define WIN_FULLSCREEN		false
#define WIN_RESIZABLE		false
#define WIN_BORDERLESS		false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC				false
#define TITLE "Pokemon Pinball"