#ifndef DRAWING_H
#define DRAWING_H

#include "structures.h"
#include <raylib.h>

void windowSetup(Color backgroundColor);
void drawGrid(Grid *grid);
void drawPlayer(float playerXMove, float playerYMove);
void drawCircleOverlay(float circleOverlayRadius);

#endif
