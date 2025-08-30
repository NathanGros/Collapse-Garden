#ifndef MODELS_H
#define MODELS_H

#include "structures.h"
#include <raylib.h>

void loadModels(Shader shadowShader);
void unloadModels();
Model *getLandModels();
Model *getWaterModels();
Model *getBridgeModels();
Model *getBridgeXModels();
Model *getBridgeUModels();
Model *getBridgeLModels();
Model *getBridgeIModels();
Model *getBridgeEndModels();
Model *getBridgeNoneModels();
Model *getFenceModels();
Model *getCloudModels();
Model *getPlayerModels();
void assignSurfaceModel(Tile *tile);
void assignBridgeModel(Tile *tile);
void assignFenceModels(Tile *tile);

#endif
