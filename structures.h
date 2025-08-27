#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <raylib.h>
#include <stdbool.h>

// Structs
typedef struct {
    bool water;
    bool bridge;
} Connection;

typedef struct {
    Model *northBridge;
    Model *eastBridge;
    Model *southBridge;
    Model *westBridge;
    Model *bridgeCenter;
    Model *water;
    int waterModelAngle;
} ModelGroup;

typedef struct {
    int posX;
    int posY;
    bool collapsed;
    Connection north;
    Connection east;
    Connection south;
    Connection west;
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

Connection makeConnection();

Tile *makeTile();
void freeTile(Tile *tile);

Grid *makeGrid(int width, int height);
void freeGrid(Grid *grid);

#endif
