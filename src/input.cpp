#include "../includes/input.hpp"

void MoveAxisWithMouse(Camera2D *camera) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {   
        SetMouseCursor(2);
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/ (*camera).zoom);

        (*camera).target = Vector2Add((*camera).target, delta);
    } 
}

void ZoomAxisWithMouseWheel(Camera2D *camera) {
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Zoom increment
        const float zoomIncrement = 0.125f;

        (*camera).zoom += (wheel*zoomIncrement);
        if ((*camera).zoom < zoomIncrement) (*camera).zoom = zoomIncrement;
    }
}

void getGameInput(Camera2D *camera, int *actualCamera, int *engine_mode) {
    MoveAxisWithMouse(camera);
    ZoomAxisWithMouseWheel(camera);

    if (IsKeyPressed(KEY_Q)) {
      if (*actualCamera == 1) {
        *actualCamera = 2;
        *engine_mode = NORMAL_MODE;
      } else {
        *actualCamera = 1;
        *engine_mode = DEBUG_MODE;
      } 
    }
}