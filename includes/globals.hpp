#pragma once
#include "raylib.h"
#include <vector>

// Engine modes
typedef enum {
    DEBUG_MODE = 0,
    NORMAL_MODE = 1,
    EDIT_MODE = 2
} EngineModes;

// Edit mode states
typedef enum {
    EDIT_MODE_STATE_SELECT = 0,
    EDIT_MODE_STATE_CREATE = 1,
    EDIT_MODE_STATE_MOVE = 2,
    EDIT_MODE_STATE_SCALE = 3
} EditModeState;

typedef enum {
    EDIT_MODE_INSPECT_MENU_HEIGHT = 300,
} EditModeMenuGUI;

// Number of buttons in the edit mode interface
#define BUTTONS_NUMBER 4

// GUI cursor states
#define CURSOR_DEFAULT 1
#define CURSOR_CROSSHAIR 3

// Game controls
#define GRID_MOVEMENT_CONTROL_CURSOR MOUSE_BUTTON_MIDDLE



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
    int mouseState;
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

typedef struct selectionBox {
    Vector2 origin;
    Vector2 position;
    Vector2 direction;
    Size size;

    // pointer to the selected blocks
    std::vector<Block> selectedBlocks;

    Rectangle rec;
} SelectionBox;

typedef struct editmode {
    int editModeState;
    int blockIdsNumber;
    std::vector<Block> blockList;
    EditModeGUI editModeInterface;
    SelectionBox selectionBox;
    Block *moveSelectedBlock;
} EditMode;

typedef struct modes {
    int engine_mode;
    EditMode editMode;
} Modes;
