#pragma once
#include "raylib.h"
#include "raymath.h"

void MoveAxisWithMouse(Camera2D *camera);

void ZoomAxisWithMouseWheel(Camera2D *camera);

void getGameInput(Camera2D *camera, int *actualCamera);
