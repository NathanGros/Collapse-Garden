#include "structures.h"
#include <stdlib.h>

Path makePath() {
    Path path;
    path.north = false;
    path.east = false;
    path.south = false;
    path.west = false;
    return path;
}

ModelGroup makeModelGroup() {
    ModelGroup modelGroup;
    return modelGroup;
}

Tile *makeTile() {
    Tile *tile = malloc(sizeof(Tile));
    tile->posX = 0;
    tile->posY = 0;
    tile->collapsed = false;
    tile->land = false;
    tile->decoration = false;
    tile->path = makePath();
    tile->surfaceRotation = 0;
    tile->bridgeRotation = 0;
    tile->modelGroup = makeModelGroup();
    return tile;
}

void freeTile(Tile *tile) { free(tile); }

Grid *makeGrid(int width, int height) {
    Grid *grid = malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;
    grid->cornerPosX = 0;
    grid->cornerPosY = 0;
    grid->nbTiles = width * height;
    grid->tiles = malloc( 2 * width * height * sizeof(Tile *)); //more space than needed for freedom
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Tile *tile = makeTile();
            tile->posX = i;
            tile->posY = j;
            grid->tiles[i * height + j] = tile;
        }
    }
    return grid;
}

void freeGrid(Grid *grid) {
    for (int i = 0; i < grid->nbTiles; i++) {
        freeTile(grid->tiles[i]);
    }
    free(grid->tiles);
    free(grid);
}
