#include "../includes/input.hpp"

void MoveAxisWithMouse(Camera2D *camera, GUI *interface) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {   
      interface->mouseState = 3;
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

void getGameInput(Camera2D *camera, int *actualCamera, Modes *mode, GUI *interface) {
    MoveAxisWithMouse(camera, interface);
    ZoomAxisWithMouseWheel(camera);

    if (IsKeyPressed(KEY_Q)) {
      if (*actualCamera == 1) {
        *actualCamera = 2;
        mode->engine_mode = NORMAL_MODE;
      } else {
        *actualCamera = 1;

        // TODO: handle this better
        mode->engine_mode = DEBUG_MODE;
      }
    }

    // Delete the selected block if in edit mode
    if (mode->engine_mode == EDIT_MODE 
    && mode->editMode.editModeState == EDIT_MODE_STATE_SELECT 
    && IsKeyPressed(KEY_DELETE) && mode->editMode.selectedBlock != -1) {
        mode->editMode.blockList.erase(mode->editMode.blockList.begin() + mode->editMode.selectedBlock);
        mode->editMode.selectedBlock = -1;
    }
}