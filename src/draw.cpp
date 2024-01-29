#include "../includes/draw.hpp"

void DrawDebugBoard(Camera2D camera) {
  Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
  // Vector2 position = GetScreenToWorld2D({ camera.target.x + camera.offset.x, camera.target.y + camera.offset.y }, camera);
  DrawText(TextFormat("Position x: %f", mousePosition.x),10,10,20, BLACK);
  DrawText(TextFormat("Position y: %f", mousePosition.y),10,30,20, BLACK);
  DrawText(TextFormat("Camera Zoom: %f", camera.zoom),10,50,20, BLACK);
  DrawText(TextFormat("Camera Target x: %f", camera.target.x),10,70,20, BLACK);
  DrawText(TextFormat("Camera Target y: %f", camera.target.y),10,90,20, BLACK);
}

void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen, Camera2D *camera) {
    int centerWidth = screen.screenWidth/2;
    int centerHeight = screen.screenHeight/2;

    rlPushMatrix();
      rlTranslatef(0, centerHeight + ((gridSpacing / 2)*(gridSize / 2)), 0);
      rlRotatef(90, 1, 0, 0);
      DrawGrid(gridSize,gridSpacing);
    rlPopMatrix();
}

void DrawGUI(Camera2D camera, Vector2 mousePosition, GUI *interface, Screen screen, Font font, int *engine_mode) {
  /**
   * @def Variables
  */
  float buttonMargin = 10.0f;
  float screenWidth = screen.screenWidth;
  float screenHeight = screen.screenHeight;

  if (!interface->isOpened && interface->position.x > screen.screenWidth - interface->width && interface->position.x < screen.screenWidth ) {
    interface->position.x += (interface->width * 2) * GetFrameTime(); // toggle GUI in 1/2 second
  }

  if (interface->isOpened && interface->position.x > screen.screenWidth - interface->width + 1 && interface->position.x < screen.screenWidth) {
    interface->position.x -= (interface->width * 2) * GetFrameTime(); // toggle GUI in 1/2 second
    if (interface->position.x < screen.screenWidth - interface->width)
      interface->position.x = screen.screenWidth - interface->width;
  }

  // Draw Toggle GUI
  Vector2 sizeToggleGUI = { 50.0f, 100.0f };
  Vector2 positionToggleGUI = { (*interface).position.x - sizeToggleGUI.x/2, screenHeight / 2 - sizeToggleGUI.y };
  Rectangle toggleGUIRec = { positionToggleGUI.x, positionToggleGUI.y, sizeToggleGUI.x, sizeToggleGUI.y };
  DrawRectangleRounded(toggleGUIRec, .5f, 10, (*interface).Toggle_color);
  DrawTextPro(
    font,
    (*interface).isOpened ? "Close" : "Open",
    {toggleGUIRec.x + (toggleGUIRec.width / 2), toggleGUIRec.y + (toggleGUIRec.height / 2)}, // Position
    {sizeToggleGUI.x /2 + 5 ,0}, // origin
    90.0f, // rotation
    20.0f, // font size
    4.0f, // spacing
    WHITE
  );

  if (CheckCollisionPointRec(mousePosition,toggleGUIRec)) {
    SetMouseCursor(4);
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      (*interface).isOpened = !(*interface).isOpened;
      if (interface->isOpened) {
        interface->position.x = screen.screenWidth - 1;
      } else {
        interface->position.x = screen.screenWidth - interface->width + 1;
      }
    }
  } else {
    SetMouseCursor(1);
  }


  // Draw GUI container
  DrawRectangle((*interface).position.x, (*interface).position.y, (*interface).width, screenHeight, (*interface).GUI_color);


  // Draw First Button
  Vector2 positionButtonOne = { (*interface).position.x + buttonMargin , (*interface).position.y + buttonMargin }; 
  Rectangle button_CreateRectangle = { positionButtonOne.x, positionButtonOne.y, (*interface).width - buttonMargin, 50 };
  if (CheckCollisionPointRec(mousePosition,button_CreateRectangle)) {
    SetMouseCursor(4);
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
    SetMouseCursor(1);
    DrawText("Create a Rectangle",button_CreateRectangle.x + (button_CreateRectangle.width / 2) - 100.0f , button_CreateRectangle.y + (button_CreateRectangle.height / 2) - 10.0f , 20.0f,WHITE);
  }
}

void DrawPlayCameraSilhouette(Camera2D camera, Screen screen) {
  Rectangle cameraSilhouette = { camera.target.x - (camera.offset.x / camera.zoom), camera.target.y - (camera.offset.y / camera.zoom), screen.screenWidth / camera.zoom, screen.screenHeight / camera.zoom };
  DrawRectangleLinesEx(cameraSilhouette, 2.0f, BLACK);
  DrawText("Play Area", (camera.target.x - (camera.offset.x / camera.zoom)) + 20, (camera.target.y - (camera.offset.y / camera.zoom)) + 20, 20, BLACK);
}
