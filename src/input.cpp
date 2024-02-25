#include "../includes/input.hpp"

void MoveAxisWithMouse(Camera2D *camera, GUI *interface) {
    if (IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR))
    {   
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f/ (*camera).zoom);

      (*camera).target = Vector2Add((*camera).target, delta);
    }

    if (IsKeyDown(KEY_A)) {
      (*camera).target.x -= 10;
    }

    if (IsKeyDown(KEY_D)) {
      (*camera).target.x += 10;
    } 
    
    if (IsKeyDown(KEY_W)) {
      (*camera).target.y -= 10;
    } 
    
    if (IsKeyDown(KEY_S)) {
      (*camera).target.y += 10;
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
    && IsKeyPressed(KEY_DELETE) && mode->editMode.selectionBox.selectedBlocks.size() != 0) {
      
      for (const auto &block : mode->editMode.selectionBox.selectedBlocks) {
        for (auto i = 0; i < (int) mode->editMode.blockList.size(); i++) {
          if (mode->editMode.blockList[i].id == block.id) {
            mode->editMode.blockList.erase(mode->editMode.blockList.begin() + i);
          }
        }
      }

      mode->editMode.selectionBox.selectedBlocks.clear();
    }

    // Save the blocks to a file
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
      createSaveFile(&mode->editMode.blockList);
    }
}