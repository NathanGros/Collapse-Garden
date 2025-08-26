#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

// Structs
typedef struct {
    bool water;
    bool bridge;
} Connection;

typedef struct {
    int posX;
    int posY;
    bool collapsed;
    Connection north;
    Connection east;
    Connection south;
    Connection west;
} Tile;

typedef struct {
    int width;
    int height;
    int cornerPosX;
    int cornerPosY;
    int nbTiles;
    Tile **tiles;
} Grid;

// Functions
Connection makeConnection();

Tile *makeTile();
void freeTile(Tile *tile);

Grid *makeGrid(int width, int height);
void freeGrid(Grid *grid);

#endif
