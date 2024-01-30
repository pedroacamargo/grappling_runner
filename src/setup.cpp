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

GUI setupGUI(int width, Screen screen) {
    GUI newGUI; 
    newGUI.GUI_color = { 37, 37, 37, 255 };
    newGUI.Button_color = { 157, 157, 157, 255 };
    newGUI.Toggle_color = { 26, 26, 26, 255 };
    newGUI.isOpened = true;
    newGUI.width = 400;
    newGUI.position = {
        (float) screen.screenWidth - newGUI.width,
        0
    };
    newGUI.toggleButton.size = { 50.0f, 100.0f };
    newGUI.toggleButton.position = { newGUI.position.x - newGUI.toggleButton.size.width/2, screen.screenHeight / 2 - newGUI.toggleButton.size.height/2 };
    return newGUI;
}