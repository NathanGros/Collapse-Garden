#include "drawing.h"
#include "models.h"
#include <raylib.h>

void windowSetup(Color backgroundColor) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1500, 900, "Collapse Garden");
    ClearBackground(backgroundColor);
    SetTargetFPS(60);
}

void drawTile(Tile *tile) {
    Vector3 pos = (Vector3){tile->posX, 0., tile->posY};
    // DrawCube(pos, 1., 1., 1., GREEN);
    if (!tile->collapsed) {
        Model *cloudModels = getCloudModels();
        DrawModelEx(cloudModels[0], pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
        return;
    }
    if (tile->modelGroup.hasNorthBridge) {
        Model *northBridgeModel = tile->modelGroup.northBridge;
        DrawModelEx(*northBridgeModel, pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
    }
    if (tile->modelGroup.hasEastBridge) {
        Model *eastBridgeModel = tile->modelGroup.eastBridge;
        DrawModelEx(*eastBridgeModel, pos, (Vector3) {0, 1, 0}, -90, (Vector3) {1, 1, 1}, WHITE);
    }
    if (tile->modelGroup.hasSouthBridge) {
        Model *southBridgeModel = tile->modelGroup.southBridge;
        DrawModelEx(*southBridgeModel, pos, (Vector3) {0, 1, 0}, 180, (Vector3) {1, 1, 1}, WHITE);
    }
    if (tile->modelGroup.hasWestBridge) {
        Model *westBridgeModel = tile->modelGroup.westBridge;
        DrawModelEx(*westBridgeModel, pos, (Vector3) {0, 1, 0}, 90, (Vector3) {1, 1, 1}, WHITE);
    }
    if (
        tile->modelGroup.hasNorthBridge ||
        tile->modelGroup.hasEastBridge ||
        tile->modelGroup.hasSouthBridge ||
        tile->modelGroup.hasWestBridge) {
        Model *bridgeCenterModels = getBridgeCenterModels();
        DrawModelEx(bridgeCenterModels[0], pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
    }

    if (tile->north.water == true) {
        DrawLine3D((Vector3){tile->posX, 0, tile->posY - 0.5}, (Vector3){tile->posX, 0, tile->posY}, BLUE);
    }
    if (tile->east.water == true) {
        DrawLine3D((Vector3){tile->posX + 0.5, 0, tile->posY}, (Vector3){tile->posX, 0, tile->posY}, BLUE);
    }
    if (tile->south.water == true) {
        DrawLine3D((Vector3){tile->posX, 0, tile->posY + 0.5}, (Vector3){tile->posX, 0, tile->posY}, BLUE);
    }
    if (tile->west.water == true) {
        DrawLine3D((Vector3){tile->posX - 0.5, 0, tile->posY}, (Vector3){tile->posX, 0, tile->posY}, BLUE);
    }
}

void drawGrid(Grid *grid) {
    for (int i = 0; i < grid->nbTiles; i++) {
        drawTile(grid->tiles[i]);
    }
}

void drawPlayer(int playerX, int playerY) {
    Vector3 playerPos = (Vector3) {(float) playerX, 0., (float) playerY};
    DrawModelEx(*getPlayerModels(), playerPos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
}

void drawCircleOverlay(float circleOverlayRadius) {
    DrawCircle(GetMouseX(), GetMouseY(), circleOverlayRadius, (Color) {255, 255, 255, 100});
}
