#pragma once
#include "raylib.h"
#include "globals.hpp"
#include "editMode.hpp"


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