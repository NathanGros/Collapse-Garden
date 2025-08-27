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
    // Draw bridges
    if (!tile->collapsed) {
        Model *cloudModels = getCloudModels();
        DrawModelEx(cloudModels[0], pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
        return;
    }
    if (tile->north.bridge) {
        Model *northBridgeModel = tile->modelGroup.northBridge;
        DrawModelEx(*northBridgeModel, pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
    }
    if (tile->east.bridge) {
        Model *eastBridgeModel = tile->modelGroup.eastBridge;
        DrawModelEx(*eastBridgeModel, pos, (Vector3) {0, 1, 0}, -90, (Vector3) {1, 1, 1}, WHITE);
    }
    if (tile->south.bridge) {
        Model *southBridgeModel = tile->modelGroup.southBridge;
        DrawModelEx(*southBridgeModel, pos, (Vector3) {0, 1, 0}, 180, (Vector3) {1, 1, 1}, WHITE);
    }
    if (tile->west.bridge) {
        Model *westBridgeModel = tile->modelGroup.westBridge;
        DrawModelEx(*westBridgeModel, pos, (Vector3) {0, 1, 0}, 90, (Vector3) {1, 1, 1}, WHITE);
    }
    if (
        tile->north.bridge ||
        tile->east.bridge ||
        tile->south.bridge ||
        tile->west.bridge) {
        Model *bridgeCenterModel = tile->modelGroup.bridgeCenter;
        DrawModelEx(*bridgeCenterModel, pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
    }
    // Draw water
    Model *waterModel = tile->modelGroup.water;
    DrawModelEx(*waterModel, pos, (Vector3) {0, 1, 0}, tile->modelGroup.waterModelAngle, (Vector3) {1, 1, 1}, WHITE);
}

void drawGrid(Grid *grid) {
    for (int i = 0; i < grid->nbTiles; i++) {
        drawTile(grid->tiles[i]);
    }
}

void drawPlayer(float playerXMove, float playerYMove) {
    Vector3 playerPos = (Vector3) {playerXMove, 0., playerYMove};
    DrawModelEx(*getPlayerModels(), playerPos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
}

void drawCircleOverlay(float circleOverlayRadius) {
    DrawCircle(GetMouseX(), GetMouseY(), circleOverlayRadius, (Color) {255, 255, 255, 100});
}
