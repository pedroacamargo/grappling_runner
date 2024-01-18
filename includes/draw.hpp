#include "raylib.h"

#ifndef __DRAW_H__
#define __DRAW_H__

#define MAX_BUILDINGS 100

void createBuildings(Rectangle *buildings, Color *buildColors, int screenHeight, int screenWidth, int spacing);

#endif