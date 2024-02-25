g++ src/files.cpp src/game.cpp src/setup.cpp src/guiComponents.cpp src/draw.cpp src/input.cpp src/editMode.cpp -o play -O1 -Wall -Wno-missing-braces -I raylib/include/ -L raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

.\play