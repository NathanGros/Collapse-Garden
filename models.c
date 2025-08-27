#include "models.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_BRIDGE_MODELS 1
#define NB_BRIDGE_CENTER_MODELS 2
#define NB_WATER_X_MODELS 1
#define NB_WATER_U_MODELS 1
#define NB_WATER_L_MODELS 1
#define NB_WATER_I_MODELS 1
#define NB_WATER_END_MODELS 1
#define NB_WATER_NONE_MODELS 1
#define NB_CLOUD_MODELS 1
#define NB_PLAYER_MODELS 1

// Models lists
Model bridgeModels[NB_BRIDGE_MODELS];
Model bridgeCenterModels[NB_BRIDGE_CENTER_MODELS];
Model waterXModels[NB_WATER_X_MODELS];
Model waterUModels[NB_WATER_U_MODELS];
Model waterLModels[NB_WATER_L_MODELS];
Model waterIModels[NB_WATER_I_MODELS];
Model waterEndModels[NB_WATER_END_MODELS];
Model waterNoneModels[NB_WATER_NONE_MODELS];
Model cloudModels[NB_CLOUD_MODELS];
Model playerModels[NB_PLAYER_MODELS];

// Getters
Model *getBridgeModels() {
    return bridgeModels;
}

Model *getBridgeCenterModels() {
    return bridgeCenterModels;
}

Model *getWaterXModels() {
    return waterXModels;
}

Model *getWaterUModels() {
    return waterUModels;
}

Model *getWaterLModels() {
    return waterLModels;
}

Model *getWaterIModels() {
    return waterIModels;
}

Model *getWaterEndModels() {
    return waterEndModels;
}

Model *getWaterNoneModels() {
    return waterNoneModels;
}

Model *getCloudModels() {
    return cloudModels;
}

Model *getPlayerModels() {
    return playerModels;
}

// Loading and unloading
void loadBridgeModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridge_%d.obj", i + 1);
        bridgeModels[i] = LoadModel(modelName);
        bridgeModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeModels() {
    for (int i = 0; i < NB_BRIDGE_MODELS; i++) {
        UnloadModel(bridgeModels[i]);
    }
}

void loadBridgeCenterModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_CENTER_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridge_centers/bridge_center_%d.obj", i + 1);
        bridgeCenterModels[i] = LoadModel(modelName);
        bridgeCenterModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeCenterModels() {
    for (int i = 0; i < NB_BRIDGE_CENTER_MODELS; i++) {
        UnloadModel(bridgeCenterModels[i]);
    }
}

void loadWaterXModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_X_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/water/water_x/water_x_%d.obj", i + 1);
        waterXModels[i] = LoadModel(modelName);
        waterXModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterXModels() {
    for (int i = 0; i < NB_WATER_X_MODELS; i++) {
        UnloadModel(waterXModels[i]);
    }
}

void loadWaterUModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_U_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/water/water_u/water_u_%d.obj", i + 1);
        waterUModels[i] = LoadModel(modelName);
        waterUModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterUModels() {
    for (int i = 0; i < NB_WATER_U_MODELS; i++) {
        UnloadModel(waterUModels[i]);
    }
}

void loadWaterLModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_L_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/water/water_l/water_l_%d.obj", i + 1);
        waterLModels[i] = LoadModel(modelName);
        waterLModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterLModels() {
    for (int i = 0; i < NB_WATER_L_MODELS; i++) {
        UnloadModel(waterLModels[i]);
    }
}

void loadWaterIModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_I_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/water/water_i/water_i_%d.obj", i + 1);
        waterIModels[i] = LoadModel(modelName);
        waterIModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterIModels() {
    for (int i = 0; i < NB_WATER_I_MODELS; i++) {
        UnloadModel(waterIModels[i]);
    }
}

void loadWaterEndModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_END_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/water/water_end/water_end_%d.obj", i + 1);
        waterEndModels[i] = LoadModel(modelName);
        waterEndModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterEndModels() {
    for (int i = 0; i < NB_WATER_END_MODELS; i++) {
        UnloadModel(waterEndModels[i]);
    }
}

void loadWaterNoneModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_NONE_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/water/water_none/water_none_%d.obj", i + 1);
        waterNoneModels[i] = LoadModel(modelName);
        waterNoneModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterNoneModels() {
    for (int i = 0; i < NB_WATER_NONE_MODELS; i++) {
        UnloadModel(waterNoneModels[i]);
    }
}

void loadCloudModels(Shader shadowShader) {
    for (int i = 0; i < NB_CLOUD_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/clouds/cloud_%d.obj", i + 1);
        cloudModels[i] = LoadModel(modelName);
        cloudModels[i].materials[0].shader = shadowShader;
    }
}

void unloadCloudModels() {
    for (int i = 0; i < NB_CLOUD_MODELS; i++) {
        UnloadModel(cloudModels[i]);
    }
}

void loadPlayerModels(Shader shadowShader) {
    for (int i = 0; i < NB_PLAYER_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/players/player_%d.obj", i + 1);
        playerModels[i] = LoadModel(modelName);
        playerModels[i].materials[0].shader = shadowShader;
    }
}

void unloadPlayerModels() {
    for (int i = 0; i < NB_PLAYER_MODELS; i++) {
        UnloadModel(playerModels[i]);
    }
}

void loadModels(Shader shadowShader) {
    loadBridgeModels(shadowShader);
    loadBridgeCenterModels(shadowShader);
    loadWaterXModels(shadowShader);
    loadWaterUModels(shadowShader);
    loadWaterLModels(shadowShader);
    loadWaterIModels(shadowShader);
    loadWaterEndModels(shadowShader);
    loadWaterNoneModels(shadowShader);
    loadCloudModels(shadowShader);
    loadPlayerModels(shadowShader);
}

void unloadModels() {
    unloadBridgeModels();
    unloadBridgeCenterModels();
    unloadWaterXModels();
    unloadWaterUModels();
    unloadWaterLModels();
    unloadWaterIModels();
    unloadWaterEndModels();
    unloadWaterNoneModels();
    unloadCloudModels();
    unloadPlayerModels();
}

void assignBridgeModels(Tile *tile) {
    if (tile->north.bridge)
        tile->modelGroup.northBridge = &bridgeModels[rand() % NB_BRIDGE_MODELS];
    if (tile->east.bridge)
        tile->modelGroup.eastBridge = &bridgeModels[rand() % NB_BRIDGE_MODELS];
    if (tile->south.bridge)
        tile->modelGroup.southBridge = &bridgeModels[rand() % NB_BRIDGE_MODELS];
    if (tile->west.bridge)
        tile->modelGroup.westBridge = &bridgeModels[rand() % NB_BRIDGE_MODELS];
}

void assignBridgeCenterModel(Tile *tile) {
    tile->modelGroup.bridgeCenter = &bridgeCenterModels[rand() % NB_BRIDGE_CENTER_MODELS];
}

void assignWaterModel(Tile *tile) {
    bool northWater = tile->north.water;
    bool eastWater = tile->east.water;
    bool southWater = tile->south.water;
    bool westWater = tile->west.water;
    int nbWater = 0;
    if (northWater) nbWater++;
    if (eastWater) nbWater++;
    if (southWater) nbWater++;
    if (westWater) nbWater++;
    if (nbWater == 4) {
        tile->modelGroup.water = &waterXModels[rand() % NB_WATER_X_MODELS];
        tile->modelGroup.waterModelAngle = rand() % 4 * 90;
    }
    else if (nbWater == 0 ) {
        tile->modelGroup.water = &waterNoneModels[rand() % NB_WATER_NONE_MODELS];
        tile->modelGroup.waterModelAngle = rand() % 4 * 90;
    }
    else if (nbWater == 3) {
        tile->modelGroup.water = &waterUModels[rand() % NB_WATER_U_MODELS];
        if (!northWater) {
            tile->modelGroup.waterModelAngle = 180;
            return;
        }
        if (!eastWater) {
            tile->modelGroup.waterModelAngle = 90;
            return;
        }
        if (!southWater) {
            tile->modelGroup.waterModelAngle = 0;
            return;
        }
        if (!westWater) {
            tile->modelGroup.waterModelAngle = -90;
            return;
        }
    }
    else if (nbWater == 2) {
        if (northWater && southWater) {
            tile->modelGroup.water = &waterIModels[rand() % NB_WATER_I_MODELS];
            tile->modelGroup.waterModelAngle = rand() % 2 * 180 + 90;
        }
        else if (eastWater && westWater) {
            tile->modelGroup.water = &waterIModels[rand() % NB_WATER_I_MODELS];
            tile->modelGroup.waterModelAngle = rand() % 2 * 180;
        }
        else {
            tile->modelGroup.water = &waterLModels[rand() % NB_WATER_L_MODELS];
            if (northWater && eastWater) {
                tile->modelGroup.waterModelAngle = 0;
                return;
            }
            if (eastWater && southWater) {
                tile->modelGroup.waterModelAngle = -90;
                return;
            }
            if (southWater && westWater) {
                tile->modelGroup.waterModelAngle = 180;
                return;
            }
            if (westWater && northWater) {
                tile->modelGroup.waterModelAngle = 90;
                return;
            }
        }
    }
    else if (nbWater == 1) {
        tile->modelGroup.water = &waterEndModels[rand() % NB_WATER_END_MODELS];
        if (northWater) {
            tile->modelGroup.waterModelAngle = 0;
            return;
        }
        if (eastWater) {
            tile->modelGroup.waterModelAngle = -90;
            return;
        }
        if (southWater) {
            tile->modelGroup.waterModelAngle = 180;
            return;
        }
        if (westWater) {
            tile->modelGroup.waterModelAngle = 90;
            return;
        }
    }
    else {
        printf("Invalid Water tile\n");
    }
}
