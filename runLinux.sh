#!/bin/bash

g++ src/files.cpp src/game.cpp src/setup.cpp src/guiComponents.cpp src/draw.cpp src/input.cpp src/editMode.cpp src/cursor.cpp -o play -Iraylib/include -Lraylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt
