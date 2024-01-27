#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "../includes/setup.hpp"

void DrawDebugBoard(Camera2D camera);

void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen, Camera2D *camera);

void DrawGUI(Camera2D camera);

void DrawPlayCameraSilhouette(Camera2D camera, Screen screen);
