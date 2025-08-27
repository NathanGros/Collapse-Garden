#ifndef BACKEND_H
#define BACKEND_H

#include "structures.h"
#include <raylib.h>

void addTile(Grid *grid, Tile *tile);
void removeTile(Grid *grid, int posX, int posY);
void collapseTile(Grid *grid, int posX, int posY);
void uncollapseTile(Grid *grid, int posX, int posY);
void collapseOneTile(Grid *grid);
void uncollapseMouseTiles(Grid *grid, Camera3D camera, float circleRadius, int playerX, int playerY);

#endif
