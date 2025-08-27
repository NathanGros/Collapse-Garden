#include "structures.h"
#include <stdlib.h>

Connection makeConnection() {
    Connection connection;
    connection.water = false;
    connection.bridge = false;
    return connection;
}

ModelGroup makeModelGroup() {
    ModelGroup modelGroup;
    modelGroup.hasNorthBridge = false;
    modelGroup.hasEastBridge = false;
    modelGroup.hasSouthBridge = false;
    modelGroup.hasWestBridge = false;
    return modelGroup;
}

Tile *makeTile() {
    Tile *tile = malloc(sizeof(Tile));
    tile->posX = 0;
    tile->posY = 0;
    tile->collapsed = false;
    tile->north = makeConnection();
    tile->east = makeConnection();
    tile->south = makeConnection();
    tile->west = makeConnection();
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
