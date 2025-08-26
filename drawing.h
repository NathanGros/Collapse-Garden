#ifndef DRAWING_H
#define DRAWING_H

#include "types.h"
#include <raylib.h>

void windowSetup(Color backgroundColor);
void drawGrid(Grid *grid);
void drawPlayer(int playerX, int playerY);
void drawCircleOverlay(float circleOverlayRadius);

#endif
