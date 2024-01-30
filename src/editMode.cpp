#include "../includes/editMode.hpp"


bool isEditModeOn(int *engine_mode) {
    if (*engine_mode == EDIT_MODE) return true;
    else return false;
}

RectangleList *initRectangleList() {
    RectangleList *recList = (RectangleList *)malloc(sizeof(RectangleList));
    recList->nextRec = NULL;
    recList->rec = { 0 };
    return recList;
}

Rectangle createRectangle(Vector2 mouseWorldPosition) {
    float recSize = 50;
    Rectangle rec = { mouseWorldPosition.x - recSize/2, mouseWorldPosition.y - recSize/2, recSize, recSize };
    return rec;
}

void editModeHandler(int *engine_mode, Vector2 mouseWorldPosition, Vector2 mousePosition, RectangleList *recList, GUI interface, Screen screen) {

    // Check if the mouse is over the GUI
    bool overwriteGUI = 
        CheckCollisionPointRec(mousePosition, {interface.position.x, interface.position.y, interface.width, (float) screen.screenHeight }) 
        || 
        CheckCollisionPointRec(mousePosition, {interface.toggleButton.position.x, interface.toggleButton.position.y, interface.toggleButton.size.width, interface.toggleButton.size.height });
    


    if (isEditModeOn(engine_mode) && !overwriteGUI) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            while(recList->nextRec != NULL) {
                recList = recList->nextRec;
            }

            Rectangle rec = createRectangle(mouseWorldPosition);
            recList->nextRec = (RectangleList *)malloc(sizeof(RectangleList));
            recList->nextRec->rec = rec;
            recList->nextRec->nextRec = NULL;
        }
    }
}

void drawRectangleList(RectangleList *recList) {
    while(recList->nextRec != NULL) {
        recList = recList->nextRec;
        DrawRectangleRec(recList->rec, RED);
    }
}

void freeRectangleList(RectangleList *recList) {
    RectangleList *aux = recList;
    while(recList->nextRec != NULL) {
        aux = recList->nextRec;
        free(recList);
        recList = aux;
    }
}