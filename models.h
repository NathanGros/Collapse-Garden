#ifndef MODELS_H
#define MODELS_H

#include "structures.h"
#include <raylib.h>

void loadModels();
void unloadModels();
Model *getBridgeModels();
Model *getBridgeCenterModels();
Model *getCloudModels();
Model *getPlayerModels();

#endif
