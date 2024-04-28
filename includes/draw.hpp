#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "setup.hpp"
#include "globals.hpp"
#include "GUI/guiComponents.hpp"
#include "GUI/sideBar.hpp"

/**
 * This function draws the grid of the engine
 * @param camera The camera to be used
*/
void DrawDebugBoard(Cursor *cursor, Camera2D camera);

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
void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen);

/**
 * This function draws the silhouette of the play camera
 * @param camera The camera to be used
 * @param screen The screen
*/
void DrawPlayCameraSilhouette(Camera2D camera, Screen screen);
