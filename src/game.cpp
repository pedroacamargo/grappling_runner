#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "../includes/draw.hpp"
#include "../includes/setup.hpp"
#include "../includes/input.hpp"
#include "../includes/globals.hpp"

int main(void) {
  Screen screen = setupWindow(1920,1080,true);

  /**
   * @def Cameras Setup
   * @param camera -  Development camera
   * @param cameraPlay - Play camera, used in play mode
  */
  Camera2D camera = setupCamera(1.0f,0.0f,{ 0, 0 }, { screen.screenWidth / 2.0f, screen.screenHeight / 2.0f });
  Camera2D cameraPlay = setupCamera(0.75f, 0.0f, { 2000, 100 }, {screen.screenWidth / 2.0f, screen.screenHeight / 2.0f });
  RenderTexture screenCamera1 = LoadRenderTexture(screen.screenWidth, screen.screenHeight);
  RenderTexture screenCamera2 = LoadRenderTexture(screen.screenWidth, screen.screenHeight);

  // Since Renderization OpenGL handle the coordinates differently, we need to flip the Y axis to draw the image
  Rectangle screenFlipped = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float) -screenCamera1.texture.height };

  /**
   * @enum 1 - Development Camera
   * @enum 2 - Play Camera
  */
  int actualCamera = 1;

  Vector2 mousePosition = { 0 };
  Font defaultFont = GetFontDefault();
  GUI interface = setupGUI(400,screen);
  int engine_mode = DEBUG_MODE;

  SetTargetFPS(60);

  // Game Loop
  while (!WindowShouldClose()) {
    mousePosition = GetMousePosition();
    getGameInput(&camera, &actualCamera);

    /**
     * @attention Development Camera
    */
    BeginTextureMode(screenCamera1);
        if (engine_mode == EDIT_MODE) ClearBackground(SKYBLUE);
        else ClearBackground(RAYWHITE);
        
        BeginMode2D(camera);

          DrawEngineGrid2D(1000, 50, screen, &camera);
          DrawPlayCameraSilhouette(cameraPlay, screen);

        EndMode2D();

        DrawGUI(camera,mousePosition,&interface,screen,defaultFont,&engine_mode);


        // Debug block code
        if (engine_mode == DEBUG_MODE) {
          DrawDebugBoard(camera);
        }

    EndTextureMode();

    // --------------------------------------------------------------------------------------------------------------------
    
    /**
     * @attention Game camera
    */
    BeginTextureMode(screenCamera2);
        ClearBackground(RAYWHITE);
      
        
        BeginMode2D(cameraPlay);

          // Debug block code
          if (engine_mode == DEBUG_MODE) {
            DrawEngineGrid2D(1000, 50, screen, &cameraPlay);
          }

        EndMode2D();

        
        // Debug block code
        if (engine_mode == DEBUG_MODE) {
          DrawDebugBoard(cameraPlay);
          DrawRectangle(screen.screenWidth/2 - 5,screen.screenHeight/2 - 5,10.0f,10.0f, BLACK);
        }

    EndTextureMode();

    // --------------------------------------------------------------------------------------------------------------------

    BeginDrawing();
      ClearBackground(RAYWHITE);

      if (actualCamera == 1) {
        DrawTextureRec(screenCamera1.texture, screenFlipped, { 0, 0 }, WHITE);
      } else {
        DrawTextureRec(screenCamera2.texture, screenFlipped, { 0, 0 }, WHITE);
      }


    EndDrawing();
  }

  CloseWindow();

  return 0;
}
