#!/bin/bash

g++ src/files.cpp src/game.cpp src/setup.cpp src/GUI/guiComponents.cpp src/GUI/sideBar.cpp src/GUI/drawGUI.cpp  src/draw.cpp src/input.cpp src/editMode.cpp src/cursor.cpp src/colors.cpp -o play -Iraylib/include -Lraylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt
