g++ src/game.cpp src/setup.cpp src/draw.cpp src/input.cpp -o play -O1 -Wall -Wno-missing-braces -I raylib/include/ -L raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

.\play