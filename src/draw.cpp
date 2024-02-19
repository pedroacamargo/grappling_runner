#include "../includes/draw.hpp"

void DrawDebugBoard(Camera2D camera) {
  Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
  // Vector2 position = GetScreenToWorld2D({ camera.target.x + camera.offset.x, camera.target.y + camera.offset.y }, camera);
  DrawText(TextFormat("Position x: %f", mousePosition.x),10,10,20, BLACK);
  DrawText(TextFormat("Position y: %f", mousePosition.y),10,30,20, BLACK);
  DrawText(TextFormat("Camera Zoom: %f", camera.zoom),10,50,20, BLACK);
  DrawText(TextFormat("Camera Target x: %f", camera.target.x),10,70,20, BLACK);
  DrawText(TextFormat("Camera Target y: %f", camera.target.y),10,90,20, BLACK);
  DrawText(TextFormat("FPS: %d", GetFPS()),10,110,20, RED);
}

void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen, Camera2D *camera, Vector2 mousePosition, GUI *interface) {
    int centerWidth = screen.screenWidth/2;
    int centerHeight = screen.screenHeight/2;
    Rectangle gridRec = { 0, 0, interface->position.x - interface->toggleButton.size.width/2, screen.screenHeight };
    Rectangle gridRec2 = { interface->position.x - interface->toggleButton.size.width/2, 0, interface->toggleButton.size.width/2, screen.screenHeight - interface->toggleButton.position.y - interface->toggleButton.size.height };
    Rectangle gridRec3 = { interface->position.x - interface->toggleButton.size.width/2, interface->toggleButton.position.y + interface->toggleButton.size.height, interface->toggleButton.size.width/2, screen.screenHeight - interface->toggleButton.position.y - interface->toggleButton.size.height };

    rlPushMatrix();
      rlTranslatef(0, centerHeight + ((gridSpacing / 2)*(gridSize / 2)), 0);
      rlRotatef(90, 1, 0, 0);
      DrawGrid(gridSize,gridSpacing);
    rlPopMatrix();


    // Check if mouse is not pressed when moving the camera, so it doesn't trigger the cursor change
    bool isMouseInGrid = CheckCollisionPointRec(mousePosition, gridRec) || CheckCollisionPointRec(mousePosition, gridRec2) || CheckCollisionPointRec(mousePosition, gridRec3);
    if (isMouseInGrid && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      interface->mouseState = 1;
    }
}

void DrawGUI(Camera2D camera, Vector2 mousePosition, GUI *interface, Screen screen, Font font, int *engine_mode) {
  /**
   * @def Variables
  */
  float buttonMargin = 10.0f;
  float buttonHeight = 50;
  float screenWidth = screen.screenWidth;
  float screenHeight = screen.screenHeight;
  int buttonNumber = 1; // !IMPORTANT

  // Animate Toggle GUI
  AnimateToggleGUI(interface, screen);
  
  // Draw Toggle GUI
  DrawToggleGUI(interface, screen, font, mousePosition);

  // Draw GUI container
  Rectangle container = {(*interface).position.x, (*interface).position.y, (*interface).width, screenHeight};
  DrawRectangleRec(container, (*interface).GUI_color);
  
  // Draw First Button
  DrawRectangleButton(engine_mode, mousePosition, buttonMargin,interface,buttonHeight);


  // if mouse is over the GUI, change the mouse state to default
  Rectangle containerAreaDefaultMouse = {(*interface).position.x, (*interface).position.y + (buttonNumber * ((buttonMargin * 2) + buttonHeight)), (*interface).width, screenHeight};
  Rectangle buttonAreaDefaultMouse = {interface->position.x, interface->position.y, buttonMargin, buttonHeight + (buttonMargin * 2)};
  Rectangle buttonAreaDefaultMouse2 = {interface->position.x, interface->position.y, interface->width, buttonMargin };
  Rectangle buttonAreaDefaultMouse3 = {interface->position.x, interface->position.y + interface->width - buttonMargin, buttonMargin, buttonHeight + (buttonMargin * 2)};

  bool isMouseInContainer = CheckCollisionPointRec(mousePosition, containerAreaDefaultMouse) || CheckCollisionPointRec(mousePosition, buttonAreaDefaultMouse) || CheckCollisionPointRec(mousePosition, buttonAreaDefaultMouse2) || CheckCollisionPointRec(mousePosition, buttonAreaDefaultMouse3);

  if (isMouseInContainer && !IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
    interface->mouseState = CURSOR_DEFAULT;
  }
}

void DrawPlayCameraSilhouette(Camera2D camera, Screen screen) {
  Rectangle cameraSilhouette = { camera.target.x - (camera.offset.x / camera.zoom), camera.target.y - (camera.offset.y / camera.zoom), screen.screenWidth / camera.zoom, screen.screenHeight / camera.zoom };
  DrawRectangleLinesEx(cameraSilhouette, 2.0f, BLACK);
  DrawText("Play Area", (camera.target.x - (camera.offset.x / camera.zoom)) + 20, (camera.target.y - (camera.offset.y / camera.zoom)) + 20, 20, BLACK);
}
