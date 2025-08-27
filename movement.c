#include "movement.h"
#include <raylib.h>

void updateCamera(Camera3D *camera, float *targetDistance) {
    // camera zoom
    *targetDistance *= 1. - 0.2 * GetMouseWheelMove();
    if (*targetDistance <= 10.) *targetDistance = 10.;
    if (*targetDistance >= 70.) *targetDistance = 70.;

    // camera position
    float pi = 3.141592;
    float verticalAngle = pi / 3.;
    float horizontalAngle = pi / 2.;
    camera->position.x = camera->target.x + *targetDistance * cos(horizontalAngle) * cos(verticalAngle);
    camera->position.y = camera->target.y + *targetDistance * sin(verticalAngle);
    camera->position.z = camera->target.z + *targetDistance * sin(horizontalAngle) * cos(verticalAngle);
}

void updateLightCamera(Camera3D *lightCamera, float playerX, float playerY) {
    lightCamera->position.x = playerX - 20.;
    lightCamera->position.y = 30.;
    lightCamera->position.z = playerY - 20.;
    lightCamera->target.x = playerX;
    lightCamera->target.z = playerY;
}

bool canPlayerMove(Grid *grid, int *playerX, int *playerY, int moveX, int moveY) {
    int nextTileIndex = -1;
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == *playerX + moveX && tile->posY == *playerY + moveY) {
            nextTileIndex = i;
        }
    }
    // Don't move if the next tile is not collapsed
    if (nextTileIndex == -1)
        return false;
    if (!grid->tiles[nextTileIndex]->collapsed)
        return false;
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
            return false;
    }
    // East
    if (moveX == 1 && moveY == 0) {
        if (!grid->tiles[currentTileIndex]->east.bridge)
            return false;
    }
    // South
    if (moveX == 0 && moveY == 1) {
        if (!grid->tiles[currentTileIndex]->south.bridge)
            return false;
    }
    // West
    if (moveX == -1 && moveY == 0) {
        if (!grid->tiles[currentTileIndex]->west.bridge)
            return false;
    }
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
    return true;
}

void executeControls(Grid *grid, int *playerX, int *playerY, float *timerMovement) {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if (canPlayerMove(grid, playerX, playerY, 0, -1)) {
            *playerX += 0;
            *playerY += -1;
            *timerMovement = 0.;
            return;
        }
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        if (canPlayerMove(grid, playerX, playerY, 1, 0)) {
            *playerX += 1;
            *playerY += 0;
            *timerMovement = 0.;
            return;
        }
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (canPlayerMove(grid, playerX, playerY, 0, 1)) {
            *playerX += 0;
            *playerY += 1;
            *timerMovement = 0.;
            return;
        }
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if (canPlayerMove(grid, playerX, playerY, -1, 0)) {
            *playerX += -1;
            *playerY += 0;
            *timerMovement = 0.;
            return;
        }
    }
}
