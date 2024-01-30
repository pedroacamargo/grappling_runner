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

  // Animate Toggle GUI
  AnimateToggleGUI(interface, screen);
  
  // Draw Toggle GUI
  DrawToggleGUI(interface, screen, font, mousePosition);

  // Draw GUI container
  DrawRectangle((*interface).position.x, (*interface).position.y, (*interface).width, screenHeight, (*interface).GUI_color);
  
  // Draw First Button
  DrawRectangleButton(engine_mode, mousePosition, buttonMargin,interface);
}

void DrawPlayCameraSilhouette(Camera2D camera, Screen screen) {
  Rectangle cameraSilhouette = { camera.target.x - (camera.offset.x / camera.zoom), camera.target.y - (camera.offset.y / camera.zoom), screen.screenWidth / camera.zoom, screen.screenHeight / camera.zoom };
  DrawRectangleLinesEx(cameraSilhouette, 2.0f, BLACK);
  DrawText("Play Area", (camera.target.x - (camera.offset.x / camera.zoom)) + 20, (camera.target.y - (camera.offset.y / camera.zoom)) + 20, 20, BLACK);
}
