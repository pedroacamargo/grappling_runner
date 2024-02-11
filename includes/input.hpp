#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.hpp"
#include "setup.hpp"

void MoveAxisWithMouse(Camera2D *camera, GUI *interface);

void ZoomAxisWithMouseWheel(Camera2D *camera);

void getGameInput(Camera2D *camera, int *actualCamera, Modes *mode, GUI *interface);
