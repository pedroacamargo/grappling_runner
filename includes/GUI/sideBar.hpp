#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "../setup.hpp"
#include "../globals.hpp"
#include "../files.hpp"

/**
 * This function draws the toggle GUI
 * The toggle GUI is a button that opens and closes the GUI
 * @param interface The GUI interface
 * @param screen The screen
 * @param font The font to be used
 * @param mousePosition The mouse position
*/
void DrawToggleGUI(GUI *interface, Screen screen, Font font, Vector2 mousePosition);

/**
 * This function draws the Edit Mode Button
 * The Edit Mode Button is a button that changes the engine mode to Edit Mode
 * @param engine_mode The engine mode
 * @param mousePosition The mouse position
 * @param buttonMargin The margin of the button
 * @param interface The GUI interface
 * @param buttonHeight The height of the button
*/
void DrawRectangleButton(int *engine_mode, Vector2 mousePosition, int buttonMargin, GUI *interface, float buttonHeight);


/**
 * This function animates the toggle GUI when closing and opening
 * @param interface The GUI interface
 * @param screen The screen
*/
void AnimateToggleGUI(GUI *interface, Screen screen);

