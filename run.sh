#!/bin/bash

clang src/game.cpp src/input.cpp src/draw.cpp src/setup.cpp -o play -Iraylib/include -Lraylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt
