#pragma once
#include "raylib.h"
#include <vector>
#define DEBUG_MODE 0
#define NORMAL_MODE 1
#define EDIT_MODE 2
#define EDIT_MODE_STATE_SELECT 0
#define EDIT_MODE_STATE_CREATE 1
#define EDIT_MODE_STATE_MOVE 2
#define EDIT_MODE_STATE_SCALE 3

typedef struct size {
    float width;
    float height;
} Size;

typedef struct screen {
    int screenWidth;
    int screenHeight;
} Screen;

typedef struct toggleButton {
    Size size;
    Vector2 position;
} GUIToggleButton;

typedef struct gui {
    Color GUI_color;
    Color Button_color;
    Color Toggle_color;
    GUIToggleButton toggleButton;
    float width;
    Vector2 position;
    bool isOpened;
} GUI;

typedef struct block {
    Rectangle rec;
    Color color;
    int id;
    int layer;
} Block;

typedef struct editmode_gui {
    Vector2 position;
    Size size;
} EditModeGUI;

typedef struct editmode {
    int editModeState;

    int selectedBlock;

    std::vector<Block> blockList;
    EditModeGUI editModeInterface;
} EditMode;

typedef struct modes {
    int engine_mode;
    EditMode editMode;
} Modes;
