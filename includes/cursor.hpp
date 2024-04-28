#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "globals.hpp"
#include "GUI/guiComponents.hpp"

void handleCursor(Cursor *cursor, Camera2D camera, GUI *interface, Screen screen, Modes *mode);

typedef struct isMouseOverBlockScaleArrows {
    bool isOver;
    int arrow;
} IsMouseOverBlockScaleArrows;
enum {
    EDIT_MODE_SCALE_ARROW_TOP = 0,
    EDIT_MODE_SCALE_ARROW_BOTTOM = 1,
    EDIT_MODE_SCALE_ARROW_LEFT = 2,
    EDIT_MODE_SCALE_ARROW_RIGHT = 3
};
IsMouseOverBlockScaleArrows isMouseOverBlockScaleArrows(Modes *mode, Cursor *cursor);