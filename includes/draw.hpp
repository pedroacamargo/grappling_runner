#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "setup.hpp"
#include "globals.hpp"
#include "guiComponents.hpp"

/**
 * This function draws the grid of the engine
 * @param camera The camera to be used
*/
void DrawDebugBoard(Camera2D camera);

/**
 * This function draws the grid of the engine
 * @param gridSize The size of the grid
 * @param gridSpacing The spacing of the grid
 * @param screen The screen
 * @param camera The camera to be used
 * @param mousePosition The mouse position
 * @param interface The GUI interface
 * @param engine_mode The engine mode
*/
void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen, Camera2D *camera, Vector2 mousePosition, GUI *interface, Modes mode);


/**
 * This function draws the main GUI of the engine and handles the mouse input for the GUI elements
 * @param camera The camera to be used
 * @param mousePosition The mouse position
 * @param interface The GUI interface
 * @param screen The screen
 * @param font The font to be used
 * @param engine_mode The engine mode
*/
void DrawGUI(Camera2D camera, Vector2 mousePosition, GUI *interface, Screen screen, Font font, int *engine_mode);

/**
 * This function draws the silhouette of the play camera
 * @param camera The camera to be used
 * @param screen The screen
*/
void DrawPlayCameraSilhouette(Camera2D camera, Screen screen);
