#include "../includes/cursor.hpp"

void handleCursor(Cursor *cursor, Camera2D camera, GUI *interface, Screen screen, Modes *mode) {

    if (mode->engine_mode == DEBUG_MODE) cursor->layer = 0;
    else if (mode->engine_mode == NORMAL_MODE) cursor->layer = 1;
    else if (mode->engine_mode == EDIT_MODE) cursor->layer = 2;

    cursor->screenPosition = GetMousePosition();
    cursor->worldPosition = GetScreenToWorld2D(cursor->screenPosition, camera);

    // --------------------------------------------------------------------------------------------------------------------> GUI
    
    Rectangle GUIdefaultArea[] = {
        {(*interface).position.x, (*interface).position.y + (GUI_BUTTONS_NUMBER * ((GUI_BUTTON_MARGIN * 2) + GUI_BUTTON_HEIGHT)), (*interface).width, screen.screenHeight},
        {interface->position.x, interface->position.y, GUI_BUTTON_MARGIN, GUI_BUTTON_HEIGHT + (GUI_BUTTON_MARGIN * 2)},
        {interface->position.x, interface->position.y, interface->width, GUI_BUTTON_MARGIN },
        {interface->position.x, interface->position.y + interface->width - GUI_BUTTON_MARGIN, GUI_BUTTON_MARGIN, GUI_BUTTON_HEIGHT + (GUI_BUTTON_MARGIN * 2)}
    };
    // if mouse is over the GUI, change the mouse state to default
    bool isMouseOverGUI = CheckCollisionPointRec(cursor->screenPosition, GUIdefaultArea[0]) ||
                              CheckCollisionPointRec(cursor->screenPosition, GUIdefaultArea[1]) || 
                              CheckCollisionPointRec(cursor->screenPosition, GUIdefaultArea[2]) || 
                              CheckCollisionPointRec(cursor->screenPosition, GUIdefaultArea[3]);

    if (isMouseOverGUI && !IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
        cursor->mouseState = CURSOR_DEFAULT;
    }

    // Toggle GUI
    Vector2 positionToggleGUI = { (*interface).position.x - interface->toggleButton.size.width/2, screen.screenHeight / 2 - interface->toggleButton.size.height/2 };
    Rectangle toggleGUIRec = { positionToggleGUI.x, positionToggleGUI.y, interface->toggleButton.size.width, interface->toggleButton.size.height };
    if (CheckCollisionPointRec(cursor->screenPosition,toggleGUIRec)) {
        cursor->mouseState = CURSOR_POINTING;
    }

    // BUTTONS
    Vector2 positionButtonOne = { (*interface).position.x + GUI_BUTTON_MARGIN , (*interface).position.y + GUI_BUTTON_MARGIN }; 
    Rectangle button_CreateRectangle = { positionButtonOne.x, positionButtonOne.y, (*interface).width - GUI_BUTTON_MARGIN, GUI_BUTTON_HEIGHT };
    if (CheckCollisionPointRec(cursor->screenPosition,button_CreateRectangle)) {
        cursor->mouseState = CURSOR_POINTING;
    }

    // --------------------------------------------------------------------------------------------------------------------> Layers

    // Grid area
    Rectangle gridRecs[] = {
        { 0, 0, interface->position.x - interface->toggleButton.size.width/2, (float) screen.screenHeight },
        { interface->position.x - interface->toggleButton.size.width/2, 0, interface->toggleButton.size.width/2, screen.screenHeight - interface->toggleButton.position.y - interface->toggleButton.size.height },
        { interface->position.x - interface->toggleButton.size.width/2, interface->toggleButton.position.y + interface->toggleButton.size.height, interface->toggleButton.size.width/2, screen.screenHeight - interface->toggleButton.position.y - interface->toggleButton.size.height }
    };

    bool isMouseInGrid = CheckCollisionPointRec(cursor->screenPosition, gridRecs[0]) || 
                         CheckCollisionPointRec(cursor->screenPosition, gridRecs[1]) ||
                         CheckCollisionPointRec(cursor->screenPosition, gridRecs[2]);

    if (cursor->layer == DEBUG_MODE) { // Debug mode

        if (isMouseInGrid && !IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
            cursor->mouseState = CURSOR_DEFAULT;
        }

        if ((isMouseInGrid || isMouseOverGUI) && IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
            cursor->mouseState = CURSOR_CROSSHAIR;
        }

    } else if (cursor->layer == NORMAL_MODE) { // Normal mode

        cursor->mouseState = CURSOR_DEFAULT;

    } else if (cursor->layer == EDIT_MODE) { // Edit mode

        if (isMouseInGrid && !IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
            cursor->mouseState = CURSOR_DEFAULT;
        }

        if ((isMouseInGrid || isMouseOverGUI) && IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
            cursor->mouseState = CURSOR_CROSSHAIR;
        }

        // Scale arrows in edit mode
        IsMouseOverBlockScaleArrows isMouseOverArrow = isMouseOverBlockScaleArrows(mode, cursor);
            
        if (isMouseOverArrow.isOver && mode->editMode.editModeState == EDIT_MODE_STATE_SCALE) {
            cursor->mouseState = CURSOR_POINTING;
        } else if (mode->editMode.editModeState == EDIT_MODE_STATE_SCALE) {
            cursor->mouseState = CURSOR_DEFAULT;
        }

    }
    


    SetMouseCursor(cursor->mouseState);
}

IsMouseOverBlockScaleArrows isMouseOverBlockScaleArrows(Modes *mode, Cursor *cursor) {
    if (&mode->editMode.scaleMode.scaleSelectedBlock->rec == nullptr) return {false, -1};

    int arrowMargin = 5;
    Rectangle *rec = &mode->editMode.scaleMode.scaleSelectedBlock->rec;
    Texture2D *arrowTexture = mode->editMode.textures.arrowTexture;


    Rectangle arrowHitboxes[] = {
        { rec->x + rec->width/2 - arrowTexture->width/2, rec->y - arrowTexture->height - arrowMargin,(float) arrowTexture->width, (float) arrowTexture->height }, // up
        { rec->x + rec->width/2 - arrowTexture->width/2, rec->y + rec->height + arrowTexture->height/3 - arrowMargin,(float) arrowTexture->width, (float) arrowTexture->height }, // down
        { rec->x - arrowTexture->width - arrowMargin, rec->y + rec->height/2 - arrowTexture->height/2,(float) arrowTexture->width, (float) arrowTexture->height }, // left
        { rec->x + rec->width + arrowTexture->width/3 - arrowMargin, rec->y + rec->height/2 - arrowTexture->height/2, (float) arrowTexture->width, (float) arrowTexture->height } // right
    };

    if (CheckCollisionPointRec(cursor->worldPosition, arrowHitboxes[EDIT_MODE_SCALE_ARROW_TOP])) return {true, EDIT_MODE_SCALE_ARROW_TOP};
    if (CheckCollisionPointRec(cursor->worldPosition, arrowHitboxes[EDIT_MODE_SCALE_ARROW_BOTTOM])) return {true, EDIT_MODE_SCALE_ARROW_BOTTOM};
    if (CheckCollisionPointRec(cursor->worldPosition, arrowHitboxes[EDIT_MODE_SCALE_ARROW_LEFT])) return {true, EDIT_MODE_SCALE_ARROW_LEFT};
    if (CheckCollisionPointRec(cursor->worldPosition, arrowHitboxes[EDIT_MODE_SCALE_ARROW_RIGHT])) return {true, EDIT_MODE_SCALE_ARROW_RIGHT};

    return {false, -1};
}