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

      *engine_mode = *engine_mode == EDIT_MODE ? DEBUG_MODE : EDIT_MODE;
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