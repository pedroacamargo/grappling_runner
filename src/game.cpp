#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "../includes/globals.hpp"
#include "../includes/setup.hpp"
#include "../includes/editMode.hpp"
#include "../includes/input.hpp"
#include "../includes/draw.hpp"

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
  /**
   * @enum 1 - Development Camera
   * @enum 2 - Play Camera
  */
  int actualCamera = 1;

  // Since Renderization OpenGL handle the coordinates differently, we need to flip the Y axis to draw the image
  Rectangle screenFlipped = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float) -screenCamera1.texture.height };


  /**
   * @def GUI Setup
  */
  Font defaultFont = GetFontDefault();
  GUI interface = setupGUI(400,screen);

  /**
   * @def Rectangle List Setup
  */
  std::vector<Block> blockList;
  EditModeGUI editModeInterface = setupEditModeGUI(screen);
  EditMode editMode;
  editMode.editModeState = EDIT_MODE_STATE_CREATE;
  editMode.selectedBlock = -1;
  editMode.blockList = blockList;
  editMode.editModeInterface = editModeInterface;
  

  /**
   * @def Mouse Position
  */
  Vector2 mousePosition = { 0 };
  Vector2 mousePositionWorld = { 0 };

  /**
   * @def Engine Mode
   * @enum 0 - Normal Mode
   * @enum 1 - Edit Mode
   * @enum 2 - Debug Mode
  */
  Modes modes = { DEBUG_MODE, editMode };

  SetTargetFPS(60);

  // Game Loop
  while (!WindowShouldClose()) {
    mousePosition = GetMousePosition();
    mousePositionWorld = GetScreenToWorld2D(mousePosition, camera);
    getGameInput(&camera, &actualCamera, &modes);

    /**
     * @attention Development Camera
    */
    BeginTextureMode(screenCamera1);
        if (modes.engine_mode == EDIT_MODE) ClearBackground(SKYBLUE);
        else ClearBackground(RAYWHITE);
        
        BeginMode2D(camera);

          DrawEngineGrid2D(1000, 50, screen, &camera);
          DrawPlayCameraSilhouette(cameraPlay, screen);
          editModeHandler(&modes, mousePositionWorld, mousePosition, interface, screen);
          drawRectangleList(modes.editMode.blockList);

        EndMode2D();

        DrawGUI(camera,mousePosition,&interface,screen,defaultFont,&modes.engine_mode);
        drawEditModeGUI(screen, &modes);

        // Debug block code
        if (modes.engine_mode == DEBUG_MODE) {
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
          if (modes.engine_mode == DEBUG_MODE) {
            DrawEngineGrid2D(1000, 50, screen, &cameraPlay);
          }

          drawRectangleList(modes.editMode.blockList);

        EndMode2D();

        
        // Debug block code
        if (modes.engine_mode == DEBUG_MODE) {
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
