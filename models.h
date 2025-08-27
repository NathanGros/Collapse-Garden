#ifndef MODELS_H
#define MODELS_H

#include "structures.h"
#include <raylib.h>

void loadModels(Shader shadowShader);
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
void assignBridgeModels(Tile *tile);
void assignBridgeCenterModel(Tile *tile);
void assignWaterModel(Tile *tile);

#endif
