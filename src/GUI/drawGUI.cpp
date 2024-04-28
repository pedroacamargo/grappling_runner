#include "../../includes/GUI/drawGUI.hpp"

void DrawGUI(Camera2D camera, Cursor cursor, GUI *interface, Screen screen, Font font, Modes *mode) {
  /**
   * @def Variables
  */
  float buttonMargin = GUI_BUTTON_MARGIN;
  float buttonHeight = GUI_BUTTON_HEIGHT;
  int buttonNumber = GUI_BUTTONS_NUMBER; // !IMPORTANT

  // Animate Toggle GUI
  AnimateToggleGUI(interface, screen);
  
  // Draw Bottom Menu
  DrawRectangleRec((Rectangle){interface->bottomMenu.position.x, interface->bottomMenu.position.y, interface->bottomMenu.size.width, interface->bottomMenu.size.height}, interface->GUI_color);

  // Draw Toggle GUI
  DrawToggleGUI(interface, screen, font, cursor.screenPosition);

  // Draw GUI container
  Rectangle container = {(*interface).position.x, (*interface).position.y, (*interface).width, (float) screen.screenHeight};
  DrawRectangleRec(container, (*interface).GUI_color);
  
  // Draw First Button
  DrawRectangleButton(&mode->engine_mode, cursor.screenPosition, buttonMargin,interface,buttonHeight);

  // Draw menu buttons
  DrawHamburguerMenu(interface, screen, mode);
}


// TODO: Change hamburguer menu when the menu is opened (add a close icon) (textured)
void DrawHamburguerMenu(GUI *interface, Screen screen, Modes *mode) {
  Texture2D texture = *interface->textures.hamburguerMenuIconTexture;
  // DrawRectangle(interface->bottomMenu.position.x, interface->bottomMenu.position.y, interface->bottomMenu.size.width, interface->bottomMenu.size.height, BLUE);
  DrawTextureEx(texture, {GUI_HAMBURGUER_MENU_BUTTON_PADDING, (float) screen.screenHeight - texture.height/2 - GUI_HAMBURGUER_MENU_BUTTON_PADDING}, 0, 0.5, interface->bottomMenu.color);

  Rectangle hamburguerMenuRec = {0, (float) screen.screenHeight - texture.height/2 - GUI_HAMBURGUER_MENU_BUTTON_PADDING - 5, (float) texture.width/2 + 10, (float) texture.height};

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