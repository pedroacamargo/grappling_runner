#include "../includes/editMode.hpp"

#define GUI_CELL_SIZE 40.0f

bool isEditModeOn(int *engine_mode) {
    if (*engine_mode == EDIT_MODE) return true;
    else return false;
}

Rectangle createRectangle(Vector2 mouseWorldPosition) {
    float recSize = 50;
    Rectangle rec = { mouseWorldPosition.x - recSize/2, mouseWorldPosition.y - recSize/2, recSize, recSize };
    return rec;
}

void editModeHandler(Modes *mode, Vector2 mouseWorldPosition, Vector2 mousePosition, GUI interface, Screen screen, Camera2D camera, Cursor *cursor) {

    // Check if the mouse is over the GUI
    bool overwriteGUI = 
        CheckCollisionPointRec(mousePosition, {interface.position.x, interface.position.y, interface.width, (float) screen.screenHeight }) 
        || 
        CheckCollisionPointRec(mousePosition, {interface.toggleButton.position.x, interface.toggleButton.position.y, interface.toggleButton.size.width, interface.toggleButton.size.height })
        ||
        CheckCollisionPointRec(mousePosition, { mode->editMode.editModeInterface.position.x, mode->editMode.editModeInterface.position.y, mode->editMode.editModeInterface.size.width, mode->editMode.editModeInterface.size.height });
    


    if ((mode->engine_mode == EDIT_MODE) 
    &&  !overwriteGUI) {

        // --------------------------------------------------------------------
        
        // Handle the create mode
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) 
        &&  mode->editMode.editModeState == EDIT_MODE_STATE_CREATE) {

            Block newBlock;
            newBlock.rec = createRectangle(mouseWorldPosition);
            newBlock.color = RED;
            
            newBlock.id = mode->editMode.blockIdsNumber;
            mode->editMode.blockIdsNumber += 1;

            newBlock.layer = 0;
            mode->editMode.blockList.push_back(newBlock);
            
        }


        // --------------------------------------------------------------------

        // First click to select the blocks and start the selection box
        // Once released, select the blocks inside the selection box
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_SELECT) {
            mode->editMode.selectionBox.selectedBlocks = {};
            mode->editMode.selectionBox.position = mouseWorldPosition;
            mode->editMode.selectionBox.origin = mouseWorldPosition;
            // TraceLog(LOG_INFO, "Mouse Position: %f, %f", mouseWorldPosition.x, mouseWorldPosition.y);
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_SELECT) {

            // Select the blocks inside the selection box after releasing the mouse button
            for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
                if (CheckCollisionRecs(mode->editMode.selectionBox.rec, mode->editMode.blockList[i].rec)) {
                    mode->editMode.selectionBox.selectedBlocks.push_back(mode->editMode.blockList[i]);
                }
            }

            mode->editMode.selectionBox.size = { 0, 0 };
            mode->editMode.selectionBox.origin = { 0, 0 };
            mode->editMode.selectionBox.position = { 0, 0 };
            mode->editMode.selectionBox.direction = { 0, 0 };
        }

        // Handle the select mode
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)
        &&  mode->editMode.editModeState == EDIT_MODE_STATE_SELECT) {

            mode->editMode.selectionBox.position = mouseWorldPosition;

            // TODO: Improve this code
            if (mode->editMode.selectionBox.origin.x > mode->editMode.selectionBox.position.x) {
                mode->editMode.selectionBox.position.x = mouseWorldPosition.x;
                mode->editMode.selectionBox.size.width = abs(mode->editMode.selectionBox.position.x - mode->editMode.selectionBox.origin.x);
                mode->editMode.selectionBox.direction.x = -1.0f;

            } else {
                mode->editMode.selectionBox.size.width = abs(mode->editMode.selectionBox.position.x - mode->editMode.selectionBox.origin.x);
                mode->editMode.selectionBox.direction.x = 1.0f;
            }

            if (mode->editMode.selectionBox.origin.y > mode->editMode.selectionBox.position.y) {
                mode->editMode.selectionBox.position.y = mouseWorldPosition.y;
                mode->editMode.selectionBox.size.height = abs(mode->editMode.selectionBox.position.y - mode->editMode.selectionBox.origin.y);
                mode->editMode.selectionBox.direction.y = -1.0f;
            } else {
                mode->editMode.selectionBox.size.height = abs(mode->editMode.selectionBox.position.y - mode->editMode.selectionBox.origin.y);
                mode->editMode.selectionBox.direction.y = 1.0f;
            }

            Color whiteOpacity = { 255, 255, 255, 100 };
            

            if (mode->editMode.selectionBox.direction.x == -1.0f && mode->editMode.selectionBox.direction.y == 1.0f) {

                mode->editMode.selectionBox.rec = { mode->editMode.selectionBox.position.x, mode->editMode.selectionBox.origin.y, mode->editMode.selectionBox.size.width, mode->editMode.selectionBox.size.height };

            } else if (mode->editMode.selectionBox.direction.y == -1.0f && mode->editMode.selectionBox.direction.x == 1.0f) {
                
                mode->editMode.selectionBox.rec = { mode->editMode.selectionBox.origin.x, mode->editMode.selectionBox.position.y, mode->editMode.selectionBox.size.width, mode->editMode.selectionBox.size.height };

            } else if (mode->editMode.selectionBox.direction.x == -1.0f && mode->editMode.selectionBox.direction.y == -1.0f) {

                mode->editMode.selectionBox.rec = { mode->editMode.selectionBox.position.x, mode->editMode.selectionBox.position.y, mode->editMode.selectionBox.size.width, mode->editMode.selectionBox.size.height };

            } else {

                mode->editMode.selectionBox.rec = { mode->editMode.selectionBox.origin.x, mode->editMode.selectionBox.origin.y, mode->editMode.selectionBox.size.width, mode->editMode.selectionBox.size.height };

            }

            // Draw the selection box
            DrawRectangleRec(mode->editMode.selectionBox.rec, whiteOpacity);

            // Paint the selected blocks with blue
            for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
                if (CheckCollisionRecs(mode->editMode.selectionBox.rec, mode->editMode.blockList[i].rec)) {
                    mode->editMode.blockList[i].color = BLUE;
                } else {
                    mode->editMode.blockList[i].color = RED;
                }
            }
        }


        // --------------------------------------------------------------------


        // Handle the move mode
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_MOVE) {

            if (mode->editMode.moveSelectedBlock != nullptr) {
                mode->editMode.moveSelectedBlock->rec.x = mouseWorldPosition.x - mode->editMode.moveSelectedBlock->rec.width/2;
                mode->editMode.moveSelectedBlock->rec.y = mouseWorldPosition.y - mode->editMode.moveSelectedBlock->rec.height/2;
            } else {
                for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
                    if (CheckCollisionPointRec(mouseWorldPosition, mode->editMode.blockList[i].rec)) {
                        mode->editMode.blockList[i].color = GREEN;

                        mode->editMode.moveSelectedBlock = &mode->editMode.blockList[i];
                    }
                }
            }

        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_MOVE) {
            for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
                mode->editMode.blockList[i].color = RED;
            }
            mode->editMode.moveSelectedBlock = nullptr;
        }


        // --------------------------------------------------------------------
        int arrowMargin = 5;
        Texture2D *arrowTexture = mode->editMode.textures.arrowTexture;
        Rectangle *rec = &mode->editMode.scaleMode.scaleSelectedBlock->rec;
        IsMouseOverBlockScaleArrows isMouseOverArrow = isMouseOverBlockScaleArrows(mode, cursor);

        if (isMouseOverArrow.isOver && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_SCALE) {
            mode->editMode.scaleMode.isScaling = isMouseOverArrow.arrow;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_SCALE) {
            mode->editMode.scaleMode.isScaling = -1;
        }

        Vector2 delta = GetMouseDelta();

        if (mode->editMode.scaleMode.isScaling != -1) {
            if (mode->editMode.scaleMode.isScaling == EDIT_MODE_SCALE_ARROW_TOP) {
                if (mode->editMode.scaleMode.flag != SCALE_MODE_FLAG_STOP_SCALING) {
                    rec->y += delta.y;
                    rec->height += -delta.y;
                } else {
                    if (delta.y < 0) {
                        rec->y += delta.y;
                        rec->height += -delta.y;
                    }
                }

                if (rec->height < MINIMUM_BLOCK_SIZE) {
                    mode->editMode.scaleMode.flag = SCALE_MODE_FLAG_STOP_SCALING;
                } else {
                    mode->editMode.scaleMode.flag = 0;
                }

            } else if (mode->editMode.scaleMode.isScaling == EDIT_MODE_SCALE_ARROW_BOTTOM) {
                mode->editMode.scaleMode.scaleSelectedBlock->rec.height += 1;
            } else if (mode->editMode.scaleMode.isScaling == EDIT_MODE_SCALE_ARROW_LEFT) {
                mode->editMode.scaleMode.scaleSelectedBlock->rec.x -= 1;
                mode->editMode.scaleMode.scaleSelectedBlock->rec.width += 1;
            } else if (mode->editMode.scaleMode.isScaling == EDIT_MODE_SCALE_ARROW_RIGHT) {
                mode->editMode.scaleMode.scaleSelectedBlock->rec.width += 1;
            }
        }
        
        if (rec != nullptr) {
            // Draw arrows around the block
            // 0: up, 1: down, 2: left, 3: right
            Vector2 positions[] = {
                { rec->x + rec->width/2 - arrowTexture->width/2, rec->y - arrowTexture->height/3 + arrowMargin }, // up
                { rec->x + rec->width/2 + arrowTexture->width/2, rec->y + rec->height + arrowTexture->height/3 - arrowMargin }, // down
                { rec->x - arrowTexture->width/3 + arrowMargin, rec->y + rec->height/2 + arrowTexture->height/2 }, // left
                { rec->x + rec->width + arrowTexture->width/3 - arrowMargin, rec->y + rec->height/2 - arrowTexture->height/2 } // right
            };

            int rotations[4] = { -90, 90, 180, 0 };
            int i = 0;

            for (Vector2 blockPosition : positions) {
                DrawTextureEx(*arrowTexture, blockPosition, rotations[i++], 1, WHITE);            
            }
        }

        // Handle the scale mode
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mode->editMode.editModeState == EDIT_MODE_STATE_SCALE) {
            if (mode->editMode.scaleMode.scaleSelectedBlock != nullptr && !isMouseOverArrow.isOver && mode->editMode.scaleMode.isScaling == -1) {
                mode->editMode.scaleMode.scaleSelectedBlock->color = RED;
                mode->editMode.scaleMode.scaleSelectedBlock = nullptr;
            } 

            for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
                if (CheckCollisionPointRec(mouseWorldPosition, mode->editMode.blockList[i].rec)) {
                    mode->editMode.scaleMode.scaleSelectedBlock = &mode->editMode.blockList[i];
                    mode->editMode.blockList[i].color = GREEN;
                } 
            }
        }
    } 
    
    if (mode->engine_mode != EDIT_MODE) {
        // Reset the colors of the blocks
        // TODO: Improve this code
        for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
            mode->editMode.blockList[i].color = RED;
            mode->editMode.selectionBox.selectedBlocks = {};
            mode->editMode.selectionBox.size = { 0, 0 };
            mode->editMode.selectionBox.origin = { 0, 0 };
            mode->editMode.selectionBox.position = { 0, 0 };
            mode->editMode.selectionBox.direction = { 0, 0 };
        }
    }
}


void drawRectangleList(std::vector<Block> blockList) {
    for (int i = 0; i < (int) blockList.size(); i++) {
        DrawRectangleRec(blockList[i].rec, blockList[i].color);

        // TODO: Write the text if in debug mode
        // DrawText(TextFormat("%i", blockList[i].id), blockList[i].rec.x + 20, blockList[i].rec.y + 20, 20, WHITE);
    }
}

EditModeGUI setupEditModeGUI(Screen screen) {
    EditModeGUI editModeInterface;
    editModeInterface.position = { 20.0f, 20.0f };
    editModeInterface.size = { (BUTTONS_NUMBER * GUI_CELL_SIZE), GUI_CELL_SIZE };
    return editModeInterface;
}

void drawEditModeGUI(Screen screen, Modes *modes, GUI interface, Vector2 mousePosition) {
    // Check if the engine is in edit mode
    if (modes->engine_mode != EDIT_MODE) return;

    // Draw the inspection menu in the bottom of GUI
    if (modes->editMode.selectionBox.selectedBlocks.size() >= 0 && modes->editMode.editModeState == EDIT_MODE_STATE_SELECT) {
        DrawRectangle(interface.position.x, interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT), interface.width, EDIT_MODE_INSPECT_MENU_HEIGHT, BLACK);

        DrawText(TextFormat("Selected Blocks: %i", modes->editMode.selectionBox.selectedBlocks.size()), interface.position.x + 10, interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT) + 10, 20, WHITE);

        if (modes->editMode.selectionBox.selectedBlocks.size() == 1) {

            // TODO: Improve this code by creating a function to get the selected block
            Block *selectedBlock = nullptr;
            for (int i = 0; i < (int) modes->editMode.blockList.size(); i++) {
                if (modes->editMode.blockList[i].id == modes->editMode.selectionBox.selectedBlocks[0].id) {
                    selectedBlock = &modes->editMode.blockList[i];
                }
            }

            DrawText(TextFormat("Block ID: %i", selectedBlock->id), interface.position.x + 10, interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT) + 30, 20, WHITE);

            float posY = interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT) + 57.5; // avoid narrowing conversion warning
            Rectangle recX = { interface.position.x + 50, posY, interface.width - 60, 32 };
            DrawRectangleRec(recX, GRAY);
            DrawText(TextFormat("X: %.2f", selectedBlock->rec.x), interface.position.x + 20, interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT) + 60, 30, WHITE);

            float posY2 = interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT) + 97.5; // avoid narrowing conversion warning
            Rectangle recY = { interface.position.x + 50, posY2, interface.width - 60, 32 };
            DrawRectangleRec(recY, GRAY);
            DrawText(TextFormat("Y: %.2f", selectedBlock->rec.y), interface.position.x + 20, interface.position.y + (screen.screenHeight - EDIT_MODE_INSPECT_MENU_HEIGHT) + 100, 30, WHITE);

            // handle the move mode
            Vector2 delta = GetMouseDelta();
            if (CheckCollisionPointRec(mousePosition,recX)) {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    selectedBlock->rec.x += delta.x;
                } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                    selectedBlock->rec.x += delta.x/4;
                }
            } else if (CheckCollisionPointRec(mousePosition,recY)) {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    selectedBlock->rec.y += delta.x;
                } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                    selectedBlock->rec.y += delta.x/4;
                }
            }

        }
    }

    // Draw the edit mode select button
    for (int i = 0; i < BUTTONS_NUMBER; i++) {
        drawEditModeSelectButton(screen, modes, i, GUI_CELL_SIZE);
    }

    Vector2 size = { modes->editMode.editModeInterface.size.width, 0 };
    Vector2 statePosition = Vector2Add(modes->editMode.editModeInterface.position,size);
    DrawRectangleV(statePosition, { 200.0f, GUI_CELL_SIZE }, BLACK);

    switch (modes->editMode.editModeState)
    {
    case EDIT_MODE_STATE_SELECT:
        DrawText("Select Mode", statePosition.x + 10.0f, modes->editMode.editModeInterface.position.y + 10.0f, 20, WHITE);
        break;
    case EDIT_MODE_STATE_CREATE:
        DrawText("Create Mode", statePosition.x + 10.0f, modes->editMode.editModeInterface.position.y + 10.0f, 20, WHITE);
        break;
    case EDIT_MODE_STATE_MOVE:
        DrawText("Move Mode", statePosition.x + 10.0f, modes->editMode.editModeInterface.position.y + 10.0f, 20, WHITE);
        break;
    case EDIT_MODE_STATE_SCALE:
        DrawText("Scale Mode", statePosition.x + 10.0f, modes->editMode.editModeInterface.position.y + 10.0f, 20, WHITE);
        break;
    }
}

void drawEditModeSelectButton(Screen screen, Modes *modes, int btnNumber, float size) {
    int selected = modes->editMode.editModeState;
    Color color = selected == btnNumber ? GRAY : BLACK;

    float positionX = modes->editMode.editModeInterface.position.x + (btnNumber * size);
    Rectangle buttonContainer = { positionX, modes->editMode.editModeInterface.position.y, size, size };

    DrawRectangleRec(buttonContainer, color);
    DrawText(TextFormat("%i", btnNumber), positionX + 15, modes->editMode.editModeInterface.position.y + 10, 20, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), buttonContainer)) {
        DrawRectangleLinesEx(buttonContainer, 2.0f, WHITE);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            modes->editMode.editModeState = btnNumber;

            // reset everything
            // TODO: Improve this code
            modes->editMode.selectionBox.selectedBlocks = {};
            modes->editMode.selectionBox.size = { 0, 0 };
            modes->editMode.selectionBox.origin = { 0, 0 };
            modes->editMode.selectionBox.position = { 0, 0 };
            modes->editMode.selectionBox.direction = { 0, 0 };
            for (int i = 0; i < (int) modes->editMode.blockList.size(); i++) {
                modes->editMode.blockList[i].color = RED;
            }
        }
    }
}