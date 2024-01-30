#include "../includes/editMode.hpp"

#define GUI_CELL_SIZE 40.0f
#define BUTTONS_NUMBER 4

bool isEditModeOn(int *engine_mode) {
    if (*engine_mode == EDIT_MODE) return true;
    else return false;
}

Rectangle createRectangle(Vector2 mouseWorldPosition) {
    float recSize = 50;
    Rectangle rec = { mouseWorldPosition.x - recSize/2, mouseWorldPosition.y - recSize/2, recSize, recSize };
    return rec;
}

void editModeHandler(Modes *mode, Vector2 mouseWorldPosition, Vector2 mousePosition, GUI interface, Screen screen) {

    // Check if the mouse is over the GUI
    bool overwriteGUI = 
        CheckCollisionPointRec(mousePosition, {interface.position.x, interface.position.y, interface.width, (float) screen.screenHeight }) 
        || 
        CheckCollisionPointRec(mousePosition, {interface.toggleButton.position.x, interface.toggleButton.position.y, interface.toggleButton.size.width, interface.toggleButton.size.height })
        ||
        CheckCollisionPointRec(mousePosition, { mode->editMode.editModeInterface.position.x, mode->editMode.editModeInterface.position.y, mode->editMode.editModeInterface.size.width, mode->editMode.editModeInterface.size.height });
    


    if (isEditModeOn(&(mode->engine_mode)) 
    &&  !overwriteGUI) {
        
        // Handle the create mode
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) 
        &&  mode->editMode.editModeState == EDIT_MODE_STATE_CREATE) {

            Block newBlock;
            newBlock.rec = createRectangle(mouseWorldPosition);
            newBlock.color = RED;
            
            // TODO: Fix the id
            newBlock.id = mode->editMode.blockList.size();

            newBlock.layer = 0;
            mode->editMode.blockList.push_back(newBlock);
            
        }

        // Handle the select mode
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
        &&  mode->editMode.editModeState == EDIT_MODE_STATE_SELECT) {

            for (int i = 0; i < (int) mode->editMode.blockList.size(); i++) {
                if (CheckCollisionPointRec(mouseWorldPosition, mode->editMode.blockList[i].rec)) {
                    mode->editMode.blockList[i].color = BLUE;
                    mode->editMode.selectedBlock = i;
                } else {
                    mode->editMode.blockList[i].color = RED;
                }
            }
        }
    }
}


void drawRectangleList(std::vector<Block> blockList) {
    for (int i = 0; i < (int) blockList.size(); i++) {
        DrawRectangleRec(blockList[i].rec, blockList[i].color);

        // TODO: Write the text if in debug mode
        DrawText(TextFormat("%i", blockList[i].id), blockList[i].rec.x + 20, blockList[i].rec.y + 20, 20, WHITE);
    }
}

EditModeGUI setupEditModeGUI(Screen screen) {
    EditModeGUI editModeInterface;
    editModeInterface.position = { 20.0f, 20.0f };
    editModeInterface.size = { (BUTTONS_NUMBER * GUI_CELL_SIZE), GUI_CELL_SIZE };
    return editModeInterface;
}

void drawEditModeGUI(Screen screen, Modes *modes) {
    // Check if the engine is in edit mode
    if (modes->engine_mode != EDIT_MODE) return;    

    // Draw the edit mode select button
    drawEditModeSelectButton(screen, modes, EDIT_MODE_STATE_SELECT, GUI_CELL_SIZE);
    drawEditModeSelectButton(screen, modes, EDIT_MODE_STATE_CREATE, GUI_CELL_SIZE);
    drawEditModeSelectButton(screen, modes, EDIT_MODE_STATE_MOVE, GUI_CELL_SIZE);
    drawEditModeSelectButton(screen, modes, EDIT_MODE_STATE_SCALE, GUI_CELL_SIZE);

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
        }
    }
}