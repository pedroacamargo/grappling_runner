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


Camera2D setupCamera(float zoom, float rotation, Vector2 target, Vector2 offset) {
    Camera2D camera = { 0 };
    camera.offset = offset;
    camera.rotation = rotation;
    camera.target = target;
    camera.zoom = zoom;

    return camera;
}