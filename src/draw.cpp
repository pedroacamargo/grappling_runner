#include "../includes/draw.hpp"

void DrawEngineGrid2D(int gridSize, int gridSpacing, Screen screen, Camera2D *camera, bool *engineDidMount) {
    int centerWidth = screen.screenWidth/2;
    int centerHeight = screen.screenHeight/2;

    rlPushMatrix();
      rlTranslatef(0, centerHeight + ((gridSpacing / 2)*(gridSize / 2)), 0);
      rlRotatef(90, 1, 0, 0);
      DrawGrid(gridSize,gridSpacing);
    rlPopMatrix();
}

void DrawGUI(Camera2D camera) {
    float offset = 5.0f;
    int GUIWidth = 400;
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight() - offset;
    Vector2 screenPosition = { screenWidth - (GUIWidth + offset), offset };
    DrawRectangle(screenPosition.x, screenPosition.y, GUIWidth, screenHeight - offset, BLACK);
    DrawText(TextFormat("x: %f", ceil(screenPosition.x)),10,70,20, BLACK);
}
