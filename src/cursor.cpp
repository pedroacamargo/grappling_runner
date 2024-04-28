#include "../includes/cursor.hpp"

void handleCursor(Cursor *cursor, Camera2D camera, GUI *interface, Screen screen, Modes *mode) {

    if (mode->engine_mode == DEBUG_MODE) cursor->layer = 0;
    else if (mode->engine_mode == PLAY_MODE) cursor->layer = 1;
    else if (mode->engine_mode == EDIT_MODE) cursor->layer = 2;

    cursor->screenPosition = GetMousePosition();
    cursor->worldPosition = GetScreenToWorld2D(cursor->screenPosition, camera);

    // --------------------------------------------------------------------------------------------------------------------> GUI
    
    // if mouse is over the GUI, change the mouse state to default
    int isMouseOverGUI = 0;
    Rectangle GUIdefaultArea[5];
    getGUIDefaultArea(interface, screen, GUIdefaultArea);
    for (int i = 0; i < 5; i++) {
        if (CheckCollisionPointRec(cursor->screenPosition, GUIdefaultArea[i])) {
            isMouseOverGUI = 1;
            break;
        }
    }
    if (isMouseOverGUI > 0 && !IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
        cursor->mouseState = CURSOR_DEFAULT;
    }

    // Toggle GUI
    Rectangle toggleGUIRec = getGUIToggleButtonArea(interface, screen);
    if (CheckCollisionPointRec(cursor->screenPosition,toggleGUIRec)) {
        cursor->mouseState = CURSOR_POINTING;
    }


    // BUTTONS
    Rectangle buttonEnterEditModeRec = getGUIButtonEnterEditModeArea(interface, screen);
    if (CheckCollisionPointRec(cursor->screenPosition,buttonEnterEditModeRec)) {
        cursor->mouseState = CURSOR_POINTING;
    }

    // Hamburguer Button (Menu)
    Rectangle hamburguerMenuRec = getGUIHamburguerMenuButtonArea(interface, screen);
    if (CheckCollisionPointRec(cursor->screenPosition, hamburguerMenuRec)) {
        cursor->mouseState = CURSOR_POINTING;
        interface->bottomMenu.color = { 0, 121, 220, 255 };
    } else interface->bottomMenu.color = WHITE;
    

    // --------------------------------------------------------------------------------------------------------------------> Layers

    // Grid area
    Rectangle gridRecs[3];
    int isMouseInGrid = 0;
    getGridArea(interface, screen, gridRecs);
    for (int i = 0; i < 3; i++) {
        if (CheckCollisionPointRec(cursor->screenPosition, gridRecs[i])) {
            isMouseInGrid = 1;
            break;
        }
    }

    if (cursor->layer == DEBUG_MODE) { // Debug mode

        if (isMouseInGrid && !IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
            cursor->mouseState = CURSOR_DEFAULT;
        }

        if ((isMouseInGrid || isMouseOverGUI) && IsMouseButtonDown(GRID_MOVEMENT_CONTROL_CURSOR)) {
            cursor->mouseState = CURSOR_CROSSHAIR;
        }

    } else if (cursor->layer == PLAY_MODE) { // Play mode

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