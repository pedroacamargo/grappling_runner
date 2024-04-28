#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "../includes/globals.hpp"
#include "../includes/setup.hpp"
#include "../includes/editMode.hpp"
#include "../includes/input.hpp"
#include "../includes/draw.hpp"
#include "../includes/files.hpp"
#include "../includes/cursor.hpp"

int main(void) {
  Screen screen = setupWindow(1920,1080,true);

  // --------------------------------------------------------------------------------------------------------------------> Textures
  Texture2D arrowTexture = LoadTexture("resources/grayArrow.png");
  Texture2D hamburguerMenuGUITexture = LoadTexture("resources/hamburguerMenuWhiteSmall.png");
  


  // --------------------------------------------------------------------------------------------------------------------> Variables

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
  interface.textures.hamburguerMenuIconTexture = &hamburguerMenuGUITexture;

  /**
   * @def Rectangle List Setup
  */
  std::vector<Block> blockList;
  EditModeGUI editModeInterface = setupEditModeGUI(screen);
  EditMode editMode = {
    .editModeState = EDIT_MODE_STATE_CREATE,
    .blockIdsNumber = 0,
    .blockList = blockList,
    .editModeInterface = editModeInterface,
    .selectionBox = {
      .origin = { 0, 0 },
      .position = { 0, 0 },
      .direction = { 0, 0 },
      .size = { 0, 0 },
      .selectedBlocks = {},
      .rec = { 0, 0, 0, 0 }
    },
    .moveSelectedBlock = nullptr,
    .textures = {
      .arrowTexture = &arrowTexture // Arrow texture when moving
    },
    .scaleMode = {
      .isScaling = -1,
      .flag = 0,
      .scaleSelectedBlock = nullptr,
      .positionArrows = nullptr
    },
  };

  // Load blocks from last save
  char filePath[] = "data/saveOne";
  readBlocksFromFile(filePath, &editMode.blockList);

  /**
   * @def Mouse Position
  */
  Vector2 mousePosition = { 0 };
  Vector2 mousePositionWorld = { 0 };

  /**
   * @def Engine Mode
   * @enum 0 - Debug Mode
   * @enum 1 - Normal Mode
   * @enum 2 - Edit Mode
  */
  Modes modes = { ACTUAL_MODE, editMode };

  /**
   * @def Cursor
   * @param layer - 0: Debug mode, 1: Normal mode, 2: Edit mode
   * @param mouseState - Cursor state
   * @param screenPosition - Mouse position on the screen
   * @param worldPosition - Mouse position on the world
  */
  Cursor cursor = {
    .layer = 0,
    .mouseState = CURSOR_DEFAULT,
    .worldPosition = { 0, 0 },
    .screenPosition = { 0, 0 },
  };

  SetTargetFPS(60);

  // Game Loop
  while (!WindowShouldClose()) {
    handleCursor(&cursor, camera, &interface, screen, &modes);
    getGameInput(&camera, &actualCamera, &modes, &interface);

    /**
     * @attention Development Camera
    */
   if (actualCamera == 1 && modes.engine_mode != PLAY_MODE) {
    BeginTextureMode(screenCamera1);
        if (modes.engine_mode == EDIT_MODE) ClearBackground(SKYBLUE);
        else ClearBackground(RAYWHITE);
        
        BeginMode2D(camera);

          DrawEngineGrid2D(1000, 50, screen);
          DrawPlayCameraSilhouette(cameraPlay, screen);
          editModeHandler(&modes, interface, screen, camera, &cursor);
          drawRectangleList(modes.editMode.blockList, &modes);

        EndMode2D();

        DrawGUI(camera,cursor,&interface,screen,defaultFont,&modes);
        drawEditModeGUI(screen, &modes, interface, &cursor);

        // Debug block code
        if (modes.engine_mode == DEBUG_MODE) {
          DrawDebugBoard(&cursor, camera);
        }

    EndTextureMode();
   }

    // --------------------------------------------------------------------------------------------------------------------
    
    /**
     * @attention Game camera
    */
   if (actualCamera == 2) {
      BeginTextureMode(screenCamera2);
          ClearBackground(RAYWHITE);
        
          
          BeginMode2D(cameraPlay);

            // Debug block code
            if (modes.engine_mode == DEBUG_MODE || modes.engine_mode == DEVELOPMENT_MODE) {
              DrawEngineGrid2D(1000, 50, screen);
            }

            drawRectangleList(modes.editMode.blockList, &modes);

          EndMode2D();

          
          // Debug block code
          if (modes.engine_mode == DEBUG_MODE || modes.engine_mode == DEVELOPMENT_MODE) {
            DrawDebugBoard(&cursor, cameraPlay);
            DrawRectangle(screen.screenWidth/2 - 5,screen.screenHeight/2 - 5,10.0f,10.0f, BLACK);
          }

      EndTextureMode();
    }
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

  UnloadTexture(arrowTexture);
  UnloadTexture(hamburguerMenuGUITexture);

  CloseWindow();

  return 0;
}
