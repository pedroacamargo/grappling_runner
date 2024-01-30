#pragma once
#include "raylib.h"
#include "globals.hpp"
#include "../includes/setup.hpp"
#include <stdlib.h>

typedef struct recList {
    Rectangle rec;
    struct recList *nextRec;
} RectangleList;

bool isEditModeOn(int *engine_mode);

RectangleList *initRectangleList();

Rectangle createRectangle(Vector2 mouseWorldPosition);

void editModeHandler(int *engine_mode, Vector2 mouseWorldPosition, Vector2 mousePosition, RectangleList *recList, GUI interface, Screen screen);

void drawRectangleList(RectangleList *recList);

void freeRectangleList(RectangleList *recList);