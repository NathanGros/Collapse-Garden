#include "movement.h"

void updateCamera(Camera3D *camera, float *targetDistance) {
    // camera zoom
    *targetDistance *= 1. - 0.2 * GetMouseWheelMove();
    if (*targetDistance <= 10.) *targetDistance = 10.;
    if (*targetDistance >= 70.) *targetDistance = 70.;

    // camera position
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float pi = 3.141592;
    float verticalAngle = pi / 3.;
    float horizontalAngle = pi / 2.;
    if (screenHeight > screenWidth) horizontalAngle = pi;
    camera->position.x = camera->target.x + *targetDistance * cos(horizontalAngle) * cos(verticalAngle);
    camera->position.y = camera->target.y + *targetDistance * sin(verticalAngle);
    camera->position.z = camera->target.z + *targetDistance * sin(horizontalAngle) * cos(verticalAngle);
}

void movePlayer(Grid *grid, int *playerX, int *playerY, int moveX, int moveY) {
    int nextTileIndex = -1;
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == *playerX + moveX && tile->posY == *playerY + moveY) {
            nextTileIndex = i;
        }
    }
    // Don't move if the next tile is not collapsed
    if (nextTileIndex == -1)
        return;
    if (!grid->tiles[nextTileIndex]->collapsed)
        return;
    int currentTileIndex = -1;
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == *playerX && tile->posY == *playerY) {
            currentTileIndex = i;
        }
    }
    // Don't move if there is no bridge
    // North
    if (moveX == 0 && moveY == -1) {
        if (!grid->tiles[currentTileIndex]->north.bridge)
            return;
    }
    // East
    if (moveX == 1 && moveY == 0) {
        if (!grid->tiles[currentTileIndex]->east.bridge)
            return;
    }
    // South
    if (moveX == 0 && moveY == 1) {
        if (!grid->tiles[currentTileIndex]->south.bridge)
            return;
    }
    // West
    if (moveX == -1 && moveY == 0) {
        if (!grid->tiles[currentTileIndex]->west.bridge)
            return;
    }
    *playerX += moveX;
    *playerY += moveY;
    // Move grid
    // North
    if (moveX == 0 && moveY == -1) {
        for (int i = 0; i < grid->width; i++) {
            removeTile(grid, grid->cornerPosX + i, grid->cornerPosY + grid->height - 1);
        }
        grid->cornerPosY -= 1;
        for (int i = 0; i < grid->width; i++) {
            Tile *newTile = makeTile();
            newTile->posX = grid->cornerPosX + i;
            newTile->posY = grid->cornerPosY;
            addTile(grid, newTile);
        }
    }
    // East
    if (moveX == 1 && moveY == 0) {
        for (int i = 0; i < grid->height; i++) {
            removeTile(grid, grid->cornerPosX, grid->cornerPosY + i);
        }
        grid->cornerPosX += 1;
        for (int i = 0; i < grid->height; i++) {
            Tile *newTile = makeTile();
            newTile->posX = grid->cornerPosX + grid->width - 1;
            newTile->posY = grid->cornerPosY + i;
            addTile(grid, newTile);
        }
    }
    // South
    if (moveX == 0 && moveY == 1) {
        for (int i = 0; i < grid->width; i++) {
            removeTile(grid, grid->cornerPosX + i, grid->cornerPosY);
        }
        grid->cornerPosY += 1;
        for (int i = 0; i < grid->width; i++) {
            Tile *newTile = makeTile();
            newTile->posX = grid->cornerPosX + i;
            newTile->posY = grid->cornerPosY + grid->height - 1;
            addTile(grid, newTile);
        }
    }
    // West
    if (moveX == -1 && moveY == 0) {
        for (int i = 0; i < grid->height; i++) {
            removeTile(grid, grid->cornerPosX + grid->width - 1, grid->cornerPosY + i);
        }
        grid->cornerPosX -= 1;
        for (int i = 0; i < grid->height; i++) {
            Tile *newTile = makeTile();
            newTile->posX = grid->cornerPosX;
            newTile->posY = grid->cornerPosY + i;
            addTile(grid, newTile);
        }
    }
}

void executeControls(Grid *grid, int *playerX, int *playerY, Camera3D *camera) {
    if (IsKeyPressed(KEY_W)) {
        movePlayer(grid, playerX, playerY, 0, -1);
        camera->target.z = *playerY;
    }
    if (IsKeyPressed(KEY_S)) {
        movePlayer(grid, playerX, playerY, 0, 1);
        camera->target.z = *playerY;
    }
    if (IsKeyPressed(KEY_A)) {
        movePlayer(grid, playerX, playerY, -1, 0);
        camera->target.x = *playerX;
    }
    if (IsKeyPressed(KEY_D)) {
        movePlayer(grid, playerX, playerY, 1, 0);
        camera->target.x = *playerX;
    }
}
