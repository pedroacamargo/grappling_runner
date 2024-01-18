#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "../includes/draw.hpp"
#include "../includes/setup.hpp"

#define MAX_BUILDINGS 100

int main(void) {
  Screen screen = setupWindow(1920,1080,true);

  Camera2D camera = { 0 };
  camera.zoom = 1.0f;

  SetTargetFPS(60);
  bool engineDidMount = false;

  // Game Loop
  while (!WindowShouldClose()) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);

        camera.target = Vector2Add(camera.target, delta);
    }
    Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawText(TextFormat("Position x: %f", mousePosition.x/100),10,10,20, BLACK);
    DrawText(TextFormat("Position y: %f", mousePosition.y/100),10,30,20, BLACK);

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Get the world point that is under the mouse
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        
        // Set the offset to where the mouse is
        camera.offset = GetMousePosition();

        // Set the target to match, so that the camera maps the world space point 
        // under the cursor to the screen space point under the cursor at any zoom
        camera.target = mouseWorldPos;

        // Zoom increment
        const float zoomIncrement = 0.125f;

        camera.zoom += (wheel*zoomIncrement);
        if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);


    int gridSize = 1000;
    int gridSpacing = 50;
    int centerWidth = screen.screenWidth/2;
    int centerHeight = screen.screenHeight/2;
    int originRadius = 10;

    rlPushMatrix();
      rlTranslatef(0, centerHeight + ((gridSpacing / 2)*(gridSize / 2) + originRadius), 0);
      rlRotatef(90, 1, 0, 0);
      DrawGrid(gridSize,gridSpacing);
    rlPopMatrix();
    DrawCircle(0, 0, originRadius, BLACK);

    if (!engineDidMount) {
      camera.target.x -= centerWidth;
      camera.target.y -= centerHeight;
      engineDidMount = true;
    }

    EndMode2D();    
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
