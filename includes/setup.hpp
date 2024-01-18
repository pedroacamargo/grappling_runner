#include "raylib.h"

#ifndef __SETUP_H__
#define __SETUP_H__

typedef struct screen {
    int screenWidth;
    int screenHeight;
} Screen;

/**
 * A function that will setup the window and create a _x_ resolution window in fullscreen
 * @param width Display width resolution
 * @param height Display height resolution
*/
Screen setupWindow(int width, int height, bool isFullScreen);

#endif