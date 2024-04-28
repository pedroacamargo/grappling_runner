#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "../setup.hpp"
#include "../globals.hpp"
#include "guiComponents.hpp"
#include "sideBar.hpp"

/**
 * This function draws the main GUI of the engine and handles the mouse input for the GUI elements
 * @param camera The camera to be used
 * @param mousePosition The mouse position
 * @param interface The GUI interface
 * @param screen The screen
 * @param font The font to be used
 * @param engine_mode The engine mode
*/
void DrawGUI(Camera2D camera, Cursor cursor, GUI *interface, Screen screen, Font font, Modes *mode);

/**
 * This function draws the bottom menu of the engine
 * @param interface The GUI interface
 * @param screen The screen
 * @param mode The engine mode
*/
void DrawHamburguerMenu(GUI *interface, Screen screen, Modes *mode);