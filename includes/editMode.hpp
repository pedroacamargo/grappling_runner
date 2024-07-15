#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.hpp"
#include <vector>
#include "../includes/setup.hpp"
#include "../includes/globals.hpp"
#include "../includes/cursor.hpp"
#include "../includes/GUI/drawGUI.hpp"
#include "../includes/colors.hpp"
#include <stdlib.h>

bool isEditModeOn(int *engine_mode);

Rectangle createRectangle(Vector2 mouseWorldPosition);

void editModeHandler(Modes *mode, GUI interface, Screen screen, Camera2D camera, Cursor *cursor);

void drawRectangleList(std::vector<Block> blockList, Modes *mode);

EditModeGUI setupEditModeGUI(Screen screen);

void drawEditModeGUI(Screen screen, Modes *modes, GUI *interface, Cursor *cursor);

void drawEditModeSelectButton(Screen screen, Modes *modes, int btnNumber, float size);

void resetEditMode(Modes *mode);