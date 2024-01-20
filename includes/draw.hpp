#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "../includes/setup.hpp"

#ifndef __DRAW_H__
#define __DRAW_H__

void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen, Camera2D *camera, bool *engineDidMount);

void DrawGUI(Camera2D camera);

#endif