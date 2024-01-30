#pragma once
#include "raylib.h"

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

typedef struct modes {
    int engine_mode;
    int editModeState;
} Modes;

/**
 * A function that will setup the window and create a _x_ resolution window in fullscreen
 * @param width Display width resolution
 * @param height Display height resolution
*/
Screen setupWindow(int width, int height, bool isFullScreen);

/**
 * A function that setup a camera (Just to reduce code and avoid repeated lines)
 * @param zoom - Camera initial zoom
 * @param rotation - Camera initial rotation
 * @param target - Camera initial target (x,y)
 * @param offset - Camera offset, give { screenWidth / 2, screenHeight / 2 } to center the camera in your screen
*/
Camera2D setupCamera(float zoom, float rotation, Vector2 target, Vector2 offset);

GUI setupGUI(int width, Screen screen);