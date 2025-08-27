#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <raylib.h>
#include <math.h>
#include "structures.h"
#include "backend.h"

void updateCamera(Camera3D *camera, float *targetDistance);
bool movePlayer(Grid *grid, int *playerX, int *playerY, int moveX, int moveY);
void executeControls(Grid *grid, int *playerX, int *playerY, Camera3D *camera, float *timerMovement);

#endif
