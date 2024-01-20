#include "../includes/input.hpp"

void MoveAxisWithMouse(Camera2D *camera) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
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
        const float zoomIncrement = 0.5f;

        (*camera).zoom += (wheel*zoomIncrement);
        if ((*camera).zoom < zoomIncrement) (*camera).zoom = zoomIncrement;
    }
}
