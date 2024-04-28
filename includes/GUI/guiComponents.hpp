#pragma once
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include "../setup.hpp"
#include "../globals.hpp"
#include "../files.hpp"

// This file contains the GUI components of the engine

/**
 * The default area of the GUI
 * It's the default area without the buttons @attention If you change the GUI buttons number, you need to change this
 * @param interface The GUI interface
 * @param screen The screen
 * @param GUIdefaultArea The default area of the GUI to be returned
*/
void getGUIDefaultArea(GUI *interface, Screen screen, Rectangle *GUIdefaultArea);

/**
 * The toggle button area of the GUI
 * @param interface The GUI interface
 * @param screen The screen
 * @return The toggle button area of the GUI
*/
Rectangle getGUIToggleButtonArea(GUI *interface, Screen screen);


/**
 * The enter edit mode button area of the GUI
 * @param interface The GUI interface
 * @param screen The screen
 * @return The enter edit mode button area of the GUI
*/
Rectangle getGUIButtonEnterEditModeArea(GUI *interface, Screen screen);


/**
 * The hamburguer menu button area of the GUI
 * @param interface The GUI interface
 * @param screen The screen
 * @return The hamburguer menu button area of the GUI
*/
Rectangle getGUIHamburguerMenuButtonArea(GUI *interface, Screen screen);

void getGridArea(GUI *interface, Screen screen, Rectangle *gridRecs);