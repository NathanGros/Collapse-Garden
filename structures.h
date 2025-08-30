#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    bool north;
    bool east;
    bool south;
    bool west;
} Path;

typedef struct {
    Model *northFence;
    Model *eastFence;
    Model *southFence;
    Model *westFence;
    Model *bridge;
    Model *surface;
} ModelGroup;

typedef struct {
    int posX;
    int posY;
    bool collapsed;
    bool land;
    bool decoration;
    Path path;
    int surfaceRotation;
    int bridgeRotation;
    ModelGroup modelGroup;
} Tile;

typedef struct {
    int width;
    int height;
    int cornerPosX;
    int cornerPosY;
    int nbTiles;
    Tile **tiles;
} Grid;

Path makePath();

Tile *makeTile();
void freeTile(Tile *tile);

Grid *makeGrid(int width, int height);
void freeGrid(Grid *grid);

#endif
