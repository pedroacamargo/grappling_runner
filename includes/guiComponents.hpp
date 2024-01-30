#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "../includes/setup.hpp"
#include "../includes/globals.hpp"


void DrawToggleGUI(GUI *interface, Screen screen, Font font, Vector2 mousePosition);

void DrawRectangleButton(int *engine_mode, Vector2 mousePosition, int buttonMargin, GUI *interface);

void AnimateToggleGUI(GUI *interface, Screen screen);