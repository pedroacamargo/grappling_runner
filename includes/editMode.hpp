#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.hpp"
#include <vector>
#include "../includes/setup.hpp"
#include "../includes/globals.hpp"
#include <stdlib.h>

bool isEditModeOn(int *engine_mode);

Rectangle createRectangle(Vector2 mouseWorldPosition);

void editModeHandler(Modes *mode, Vector2 mouseWorldPosition, Vector2 mousePosition, GUI interface, Screen screen);

void drawRectangleList(std::vector<Block> blockList);

EditModeGUI setupEditModeGUI(Screen screen);

void drawEditModeGUI(Screen screen, Modes *modes);

void drawEditModeSelectButton(Screen screen, Modes *modes, int btnNumber, float size);