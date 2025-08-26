#ifndef BACKEND_H
#define BACKEND_H

#include "types.h"

void addTile(Grid *grid, Tile *tile);
void removeTile(Grid *grid, int posX, int posY);
void collapseTile(Grid *grid, int posX, int posY);
void uncollapseTile(Grid *grid, int posX, int posY);
void collapseOneTile(Grid *grid);

#endif
