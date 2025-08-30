#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"
#include <raylib.h>

void windowSetup(Color backgroundColor);
void drawFences(Grid *grid);
void drawGrid(Grid *grid);
void drawGround(Color backgroundColor, Grid *grid, Model *ground);
void drawPlayer(float playerXMove, float playerYMove);
void drawCircleOverlay(float circleOverlayRadius);

#endif
