#include "../includes/guiComponents.hpp"

void DrawToggleGUI(GUI *interface, Screen screen, Font font, Vector2 mousePosition) {
  Vector2 positionToggleGUI = { (*interface).position.x - interface->toggleButton.size.width/2, screen.screenHeight / 2 - interface->toggleButton.size.height/2 };
  Rectangle toggleGUIRec = { positionToggleGUI.x, positionToggleGUI.y, interface->toggleButton.size.width, interface->toggleButton.size.height };

  DrawRectangleRounded(toggleGUIRec, .5f, 10, (*interface).Toggle_color);
  DrawTextPro(
    font,
    (*interface).isOpened ? "Close" : "Open",
    {toggleGUIRec.x + (toggleGUIRec.width / 2), toggleGUIRec.y + (toggleGUIRec.height / 2)}, // Position
    {interface->toggleButton.size.width/2 + 5 ,0}, // origin
    90.0f, // rotation
    20.0f, // font size
    4.0f, // spacing
    WHITE
  );

  // Toggle GUI
  if (CheckCollisionPointRec(mousePosition,toggleGUIRec)) {
    interface->mouseState = CURSOR_POINTING;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      (*interface).isOpened = !(*interface).isOpened;
      if (interface->isOpened) {
        interface->position.x = screen.screenWidth - 1;
      } else {
        interface->position.x = screen.screenWidth - interface->width + 1;
      }
    }
  }
}

void DrawRectangleButton(int *engine_mode, Vector2 mousePosition, int buttonMargin, GUI *interface, float buttonHeight) {
  Vector2 positionButtonOne = { (*interface).position.x + buttonMargin , (*interface).position.y + buttonMargin }; 
  Rectangle button_CreateRectangle = { positionButtonOne.x, positionButtonOne.y, (*interface).width - buttonMargin, buttonHeight };

  if (CheckCollisionPointRec(mousePosition,button_CreateRectangle)) {
    
    interface->mouseState = CURSOR_POINTING;

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      DrawRectangleRec(button_CreateRectangle,WHITE);
      DrawText("Create a Rectangle",button_CreateRectangle.x + (button_CreateRectangle.width / 2) - 100.0f , button_CreateRectangle.y + (button_CreateRectangle.height / 2) - 10.0f , 20.0f,BLACK);

      *engine_mode = *engine_mode == EDIT_MODE ? ACTUAL_MODE : EDIT_MODE;
    } else {
      DrawRectangleRec(button_CreateRectangle,{200,200,200,255});
      DrawText("Create a Rectangle",button_CreateRectangle.x + (button_CreateRectangle.width / 2) - 100.0f , button_CreateRectangle.y + (button_CreateRectangle.height / 2) - 10.0f , 20.0f,BLACK);
    }
  } else {
    DrawRectangleRec(button_CreateRectangle,interface->Button_color);
    DrawText("Create a Rectangle",button_CreateRectangle.x + (button_CreateRectangle.width / 2) - 100.0f , button_CreateRectangle.y + (button_CreateRectangle.height / 2) - 10.0f , 20.0f,WHITE);
  }
}

void AnimateToggleGUI(GUI *interface, Screen screen) {
  if (!interface->isOpened && interface->position.x > screen.screenWidth - interface->width && interface->position.x < screen.screenWidth ) {
    interface->position.x += (interface->width) * GetFrameTime(); // toggle GUI in 1/2 second

    // Prevent GUI from going off screen
    if (interface->position.x >= screen.screenWidth) {
      interface->position.x = screen.screenWidth;
      interface->toggleButton.position.x = interface->position.x - interface->toggleButton.size.width/2;
    }
  }

  if (interface->isOpened && interface->position.x > screen.screenWidth - interface->width + 1 && interface->position.x <= screen.screenWidth) {
    interface->position.x -= (interface->width) * GetFrameTime(); // toggle GUI in 1/2 second

    // Prevent GUI from going off screen
    if (interface->position.x < screen.screenWidth - interface->width) {
      interface->position.x = screen.screenWidth - interface->width;
      interface->toggleButton.position.x = interface->position.x - interface->toggleButton.size.width/2;
    }
  }

}

// TODO: Change hamburguer menu when the menu is opened (add a close icon) (textured)
void DrawHamburguerMenu(GUI *interface, Screen screen, Modes *mode) {
  Texture2D texture = *interface->textures.hamburguerMenuIconTexture;
  // DrawRectangle(interface->bottomMenu.position.x, interface->bottomMenu.position.y, interface->bottomMenu.size.width, interface->bottomMenu.size.height, BLUE);
  DrawTextureEx(texture, {GUI_HAMBURGUER_MENU_BUTTON_PADDING, (float) screen.screenHeight - texture.height/2 - GUI_HAMBURGUER_MENU_BUTTON_PADDING}, 0, 0.5, interface->bottomMenu.color);

  Rectangle hamburguerMenuRec = {0, (float) screen.screenHeight - texture.height/2 - GUI_HAMBURGUER_MENU_BUTTON_PADDING - 5, texture.width/2 + 10, texture.height};

  if (CheckCollisionPointRec(GetMousePosition(),hamburguerMenuRec)) {
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      interface->bottomMenu.isOpened = !interface->bottomMenu.isOpened;
      interface->bottomMenu.fileWasSavedResponse = 0;
    }
  }



  Rectangle menu = (Rectangle) {5, screen.screenHeight - interface->bottomMenu.size.height - 40, 100, 40};
  Color color = BLACK;
  if (interface->bottomMenu.isOpened) {



    if (CheckCollisionPointRec(GetMousePosition(),menu)) {
      color = DARKGRAY;
      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        interface->bottomMenu.fileWasSavedResponse = createSaveFile(&mode->editMode.blockList);
      }
    }

    if (interface->bottomMenu.fileWasSavedResponse == 1) {
      DrawText("Game saved successfully!", interface->bottomMenu.position.x + 50 * GUI_BOTTOM_MENU_BUTTONS_NUMBER, screen.screenHeight - 25, 10, GRAY);
    } else if (interface->bottomMenu.fileWasSavedResponse == -1) {
      DrawText("Error saving file", interface->bottomMenu.position.x + 50 * GUI_BOTTOM_MENU_BUTTONS_NUMBER, screen.screenHeight - 25, 10, GRAY);
    }

    DrawRectangle(menu.x, menu.y, menu.width, menu.height, color);
    DrawRectangleRoundedLines(menu, .3, 10, 2, GRAY);
    DrawText("Save", menu.x + 10, menu.y + 10, 20, WHITE);
  }


}