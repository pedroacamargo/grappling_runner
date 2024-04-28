#include "../includes/draw.hpp"

void DrawDebugBoard(Cursor *cursor, Camera2D camera) {
  DrawText(TextFormat("Position x: %f", cursor->worldPosition.x),10,10,20, BLACK);
  DrawText(TextFormat("Position y: %f", cursor->worldPosition.y),10,30,20, BLACK);
  DrawText(TextFormat("Camera Zoom: %f", camera.zoom),10,50,20, BLACK);
  DrawText(TextFormat("Camera Target x: %f", camera.target.x),10,70,20, BLACK);
  DrawText(TextFormat("Camera Target y: %f", camera.target.y),10,90,20, BLACK);
  DrawText(TextFormat("FPS: %d", GetFPS()),10,110,20, RED);
}

void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen) {   
    rlPushMatrix();
      rlTranslatef(0, (screen.screenHeight/2) + ((gridSpacing / 2)*(gridSize / 2)), 0);
      rlRotatef(90, 1, 0, 0);
      DrawGrid(gridSize,gridSpacing);
    rlPopMatrix();
}

void DrawPlayCameraSilhouette(Camera2D camera, Screen screen) {
  Rectangle cameraSilhouette = { camera.target.x - (camera.offset.x / camera.zoom), camera.target.y - (camera.offset.y / camera.zoom), screen.screenWidth / camera.zoom, screen.screenHeight / camera.zoom };
  DrawRectangleLinesEx(cameraSilhouette, 2.0f, BLACK);
  DrawText("Play Area", (camera.target.x - (camera.offset.x / camera.zoom)) + 20, (camera.target.y - (camera.offset.y / camera.zoom)) + 20, 20, BLACK);
}