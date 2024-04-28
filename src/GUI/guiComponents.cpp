#include "../../includes/GUI/guiComponents.hpp"

void getGUIDefaultArea(GUI *interface, Screen screen, Rectangle *GUIdefaultArea) {

    GUIdefaultArea[0] = {
        (*interface).position.x, 
        (*interface).position.y + (GUI_BUTTONS_NUMBER * ((GUI_BUTTON_MARGIN * 2) + GUI_BUTTON_HEIGHT)), 
        (*interface).width,
        (float) screen.screenHeight
    };

    GUIdefaultArea[1] = {
        (*interface).position.x,
        (*interface).position.y,
        GUI_BUTTON_MARGIN, 
        GUI_BUTTON_HEIGHT + (GUI_BUTTON_MARGIN * 2)
    };

    GUIdefaultArea[2] = {
        (*interface).position.x, 
        (*interface).position.y, 
        (*interface).width, 
        GUI_BUTTON_MARGIN
    };

    GUIdefaultArea[3] = {
        (*interface).position.x,
        (*interface).position.y + (*interface).width - GUI_BUTTON_MARGIN, 
        GUI_BUTTON_MARGIN, 
        GUI_BUTTON_HEIGHT + (GUI_BUTTON_MARGIN * 2)
    };
    
    GUIdefaultArea[4] = {
        (*interface).position.x + (*interface).width - GUI_BUTTON_MARGIN, 
        (*interface).position.y, 
        GUI_BUTTON_MARGIN, 
        GUI_BUTTON_HEIGHT + (GUI_BUTTON_MARGIN * 2)
    };

}

Rectangle getGUIToggleButtonArea(GUI *interface, Screen screen) {

    Vector2 positionToggleGUI = { (*interface).position.x - interface->toggleButton.size.width/2, screen.screenHeight / 2 - interface->toggleButton.size.height/2 };
    Rectangle toggleGUIRec = { positionToggleGUI.x, positionToggleGUI.y, interface->toggleButton.size.width, interface->toggleButton.size.height };

    return toggleGUIRec;
}

Rectangle getGUIButtonEnterEditModeArea(GUI *interface, Screen screen) {
    Vector2 positionButtonOne = { (*interface).position.x + GUI_BUTTON_MARGIN , (*interface).position.y + GUI_BUTTON_MARGIN }; 
    Rectangle buttonEnterEditModeArea = { positionButtonOne.x, positionButtonOne.y, (*interface).width - GUI_BUTTON_MARGIN, GUI_BUTTON_HEIGHT };
    return buttonEnterEditModeArea;
}

Rectangle getGUIHamburguerMenuButtonArea(GUI *interface, Screen screen) {
    Texture2D texture = *interface->textures.hamburguerMenuIconTexture;
    Rectangle hamburguerMenuRec = (Rectangle){0, (float) screen.screenHeight - texture.height/2 - 5, (float) texture.width/2 + GUI_HAMBURGUER_MENU_BUTTON_PADDING, (float) texture.height/2 + GUI_HAMBURGUER_MENU_BUTTON_PADDING};
    return hamburguerMenuRec;
}


void getGridArea(GUI *interface, Screen screen, Rectangle *gridRecs) {
    
    gridRecs[0] = {
        0,
        0,
        interface->position.x - interface->toggleButton.size.width/2,
        (float) screen.screenHeight - interface->bottomMenu.size.height
    };

    gridRecs[1] = {
        interface->position.x - interface->toggleButton.size.width/2, 
        0,
        interface->toggleButton.size.width/2, 
        screen.screenHeight - interface->toggleButton.position.y - interface->toggleButton.size.height
    };

    gridRecs[2] = {
        interface->position.x - interface->toggleButton.size.width/2,
        interface->toggleButton.position.y + interface->toggleButton.size.height,
        interface->toggleButton.size.width/2,
        screen.screenHeight - interface->toggleButton.position.y - interface->toggleButton.size.height
    };

}