#include "drawing.h"

void windowSetup(Color backgroundColor) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1500, 900, "Collapse Garden");
    ClearBackground(backgroundColor);
    SetTargetFPS(60);
}

void drawTile(Tile *tile) {
    Vector3 pos = (Vector3){tile->posX, 0., tile->posY};
    if (!tile->collapsed) {
        DrawCube(pos, 1., 1., 1., RAYWHITE);
        return;
    }
    DrawCube(pos, 1., 1., 1., GREEN);
    if (tile->north.water == true) {
        DrawLine3D((Vector3){tile->posX, 0.6, tile->posY - 0.5}, (Vector3){tile->posX, 0.6, tile->posY}, BLUE);
    }
    if (tile->east.water == true) {
        DrawLine3D((Vector3){tile->posX + 0.5, 0.6, tile->posY}, (Vector3){tile->posX, 0.6, tile->posY}, BLUE);
    }
    if (tile->south.water == true) {
        DrawLine3D((Vector3){tile->posX, 0.6, tile->posY + 0.5}, (Vector3){tile->posX, 0.6, tile->posY}, BLUE);
    }
    if (tile->west.water == true) {
        DrawLine3D((Vector3){tile->posX - 0.5, 0.6, tile->posY}, (Vector3){tile->posX, 0.6, tile->posY}, BLUE);
    }
    if (tile->north.bridge == true) {
        DrawLine3D((Vector3){tile->posX, 0.8, tile->posY - 0.5}, (Vector3){tile->posX, 0.8, tile->posY}, RED);
    }
    if (tile->east.bridge == true) {
        DrawLine3D((Vector3){tile->posX + 0.5, 0.8, tile->posY}, (Vector3){tile->posX, 0.8, tile->posY}, RED);
    }
    if (tile->south.bridge == true) {
        DrawLine3D((Vector3){tile->posX, 0.8, tile->posY + 0.5}, (Vector3){tile->posX, 0.8, tile->posY}, RED);
    }
    if (tile->west.bridge == true) {
        DrawLine3D((Vector3){tile->posX - 0.5, 0.8, tile->posY}, (Vector3){tile->posX, 0.8, tile->posY}, RED);
    }
}

void drawGrid(Grid *grid) {
    for (int i = 0; i < grid->nbTiles; i++) {
        drawTile(grid->tiles[i]);
    }
}

void drawPlayer(int playerX, int playerY) {
    Vector3 playerPos = (Vector3) {(float) playerX, 1., (float) playerY};
    DrawCube(playerPos, 0.2, 0.2, 0.2, YELLOW);
    DrawCubeWires(playerPos, 0.2, 0.2, 0.2, BLACK);
}

void drawCircleOverlay(float circleOverlayRadius) {
    DrawCircle(GetMouseX(), GetMouseY(), circleOverlayRadius, (Color) {255, 255, 255, 100});
}
