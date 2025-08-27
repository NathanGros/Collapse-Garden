#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <raylib.h>
#include <math.h>
#include "structures.h"
#include "backend.h"

void updateCamera(Camera3D *camera, float *targetDistance);
void updateLightCamera(Camera3D *lightCamera, float playerX, float playerY);
void executeControls(Grid *grid, int *playerX, int *playerY, float *timerMovement);

#endif
