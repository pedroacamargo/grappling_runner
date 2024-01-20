#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "../includes/draw.hpp"
#include "../includes/setup.hpp"
#include "../includes/input.hpp"

#define MAX_BUILDINGS 100

int main(void) {
  Screen screen = setupWindow(1920,1080,true);

  Camera2D camera = { 0 };
  camera.zoom = 1.0f;
  camera.rotation = 0.0f;
  camera.target = (Vector2) { screen.screenWidth / 2.0f, screen.screenHeight / 2.0f };
  camera.offset = (Vector2) { screen.screenWidth / 2.0f, screen.screenHeight / 2.0f };

  SetTargetFPS(60);
  bool engineDidMount = false;
  // Game Loop
  while (!WindowShouldClose()) {
    MoveAxisWithMouse(&camera);
    ZoomAxisWithMouseWheel(&camera);

    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawText(TextFormat("Position x: %f", mousePosition.x/100),10,10,20, BLACK);
    DrawText(TextFormat("Position y: %f", mousePosition.y/100),10,30,20, BLACK);
    DrawText(TextFormat("Camera Zoom: %f", camera.zoom),10,50,20, BLACK);


    BeginDrawing();
    
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    DrawEngineGrid2D(1000, 50, screen, &camera, &engineDidMount);

    EndMode2D();


    DrawGUI(camera);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
