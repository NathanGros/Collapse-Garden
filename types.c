#include "types.h"
#include <stdlib.h>

Connection makeConnection() {
    Connection connection;
    connection.water = false;
    connection.bridge = false;
    return connection;
}

Tile *makeTile() {
    Tile *tile = malloc(sizeof(Tile));
    tile->posX = 0;
    tile->posY = 0;
    tile->north = makeConnection();
    tile->east = makeConnection();
    tile->south = makeConnection();
    tile->west = makeConnection();
    return tile;
}

void freeTile(Tile *tile) { free(tile); }

Grid *makeGrid(int width, int height) {
    Grid *grid = malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;
    grid->tiles = malloc(width * height * sizeof(Tile *));
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
    for (int i = 0; i < grid->width * grid->height; i++) {
        freeTile(grid->tiles[i]);
    }
    free(grid->tiles);
    free(grid);
}
