#ifndef MODELS_H
#define MODELS_H

#include "structures.h"
#include <raylib.h>

void loadModels();
void unloadModels();
Model *getBridgeModels();
Model *getBridgeCenterModels();
Model *getWaterXModels();
Model *getWaterUModels();
Model *getWaterLModels();
Model *getWaterIModels();
Model *getWaterEndModels();
Model *getWaterNoneModels();
Model *getCloudModels();
Model *getPlayerModels();
void assignWaterModel(Tile *tile);

#endif
