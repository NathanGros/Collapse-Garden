#include "drawing.h"
#include "models.h"
#include <raylib.h>

void windowSetup(Color backgroundColor) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1500, 900, "Collapse Garden");
    ClearBackground(backgroundColor);
    SetTargetFPS(60);
}

void drawFences(Grid *grid) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (!tile->collapsed || !tile->land)
            continue;
        Vector3 pos = (Vector3){tile->posX, 0., tile->posY};
        // North Fence
        for (int j = 0; j < grid->nbTiles; j++) {
            Tile *otherTile = grid->tiles[j];
            if (!otherTile->collapsed || !otherTile->land || tile->path.north)
                continue;
            if (tile->posX == otherTile->posX && tile->posY - 1 == otherTile->posY) {
                Model *fenceModel = tile->modelGroup.northFence;
                DrawModelEx(*fenceModel, pos, (Vector3) {0, 1, 0}, 90, (Vector3) {1, 1, 1}, WHITE);
            }
        }
        // East Fence
        for (int j = 0; j < grid->nbTiles; j++) {
            Tile *otherTile = grid->tiles[j];
            if (!otherTile->collapsed || !otherTile->land || tile->path.east)
                continue;
            if (tile->posX + 1 == otherTile->posX && tile->posY == otherTile->posY) {
                Model *fenceModel = tile->modelGroup.eastFence;
                DrawModelEx(*fenceModel, pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
            }
        }
    }
}

void drawTile(Tile *tile) {
    Vector3 pos = (Vector3){tile->posX, 0., tile->posY};
    if (!tile->collapsed) {
        // Model *cloudModels = getCloudModels();
        // DrawModelEx(cloudModels[0], pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
        return;
    }
    // Draw surface
    Model *surfaceModel = tile->modelGroup.surface;
    DrawModelEx(*surfaceModel, pos, (Vector3) {0, 1, 0}, tile->surfaceRotation, (Vector3) {1, 1, 1}, WHITE);
    // Draw bridge
    if (!tile->land) {
        Model *bridgeModel = tile->modelGroup.bridge;
        if (!tile->decoration && !tile->path.north && !tile->path.east && !tile->path.south && !tile->path.west)
            return;
        DrawModelEx(*bridgeModel, pos, (Vector3) {0, 1, 0}, tile->bridgeRotation, (Vector3) {1, 1, 1}, WHITE);
    }
}

void drawGrid(Grid *grid) {
    for (int i = 0; i < grid->nbTiles; i++) {
        drawTile(grid->tiles[i]);
    }
}

void drawGround(Color backgroundColor, Grid *grid, Model *ground) {
    Vector3 pos = (Vector3) {grid->cornerPosX + grid->width / 2., 0., grid->cornerPosY + grid->height / 2.};
    DrawModelEx(*ground, pos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, backgroundColor);
}

void drawPlayer(float playerXMove, float playerYMove) {
    Vector3 playerPos = (Vector3) {playerXMove, 0., playerYMove};
    DrawModelEx(*getPlayerModels(), playerPos, (Vector3) {0, 1, 0}, 0, (Vector3) {1, 1, 1}, WHITE);
}

void drawCircleOverlay(float circleOverlayRadius) {
    DrawCircle(GetMouseX(), GetMouseY(), circleOverlayRadius, (Color) {255, 255, 255, 100});
}
