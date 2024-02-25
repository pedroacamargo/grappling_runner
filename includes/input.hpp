#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.hpp"
#include "setup.hpp"
#include "files.hpp"

void MoveAxisWithMouse(Camera2D *camera, GUI *interface, Modes *mode);

void ZoomAxisWithMouseWheel(Camera2D *camera);

void getGameInput(Camera2D *camera, int *actualCamera, Modes *mode, GUI *interface);
