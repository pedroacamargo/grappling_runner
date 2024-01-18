#include "../includes/draw.hpp"

void createBuildings(Rectangle *buildings, Color *buildColors, int screenHeight, int screenWidth, int spacing) {
    for (int i = 0; i < MAX_BUILDINGS; i++) {
        buildings[i].width = (float) GetRandomValue(50, 200);
        buildings[i].height = (float) GetRandomValue(100, 800);
        buildings[i].y = screenHeight - 130.0f - buildings[i].height;
        buildings[i].x = -6000.0f + spacing;
        spacing += (int) buildings[i].width;

        buildColors[i] = (Color) { (unsigned char) GetRandomValue(200, 240), (unsigned char) GetRandomValue(200, 240), (unsigned char) GetRandomValue(200, 250), 255 };
    }
}