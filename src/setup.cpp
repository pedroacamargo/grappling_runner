#include "../includes/setup.hpp"
#include <stdio.h>


Screen setupWindow(int width, int height, bool isFullScreen) {
    Screen screen;
    
    const int screenWidth = width;
    const int screenHeight = height;
    screen.screenHeight = screenHeight;
    screen.screenWidth = screenWidth;

    InitWindow(screenWidth, screenHeight, "Grappling");
    if (isFullScreen) ToggleFullscreen();    

    return screen;
}