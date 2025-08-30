#include "models.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_LAND_MODELS 1
#define NB_WATER_MODELS 1
#define NB_BRIDGE_X_MODELS 1
#define NB_BRIDGE_U_MODELS 1
#define NB_BRIDGE_L_MODELS 4
#define NB_BRIDGE_I_MODELS 1
#define NB_BRIDGE_END_MODELS 1
#define NB_BRIDGE_NONE_MODELS 1
#define NB_FENCE_MODELS 1
#define NB_CLOUD_MODELS 1
#define NB_PLAYER_MODELS 1

// Models lists
Model landModels[NB_LAND_MODELS];
Model waterModels[NB_WATER_MODELS];
Model bridgeXModels[NB_BRIDGE_X_MODELS];
Model bridgeUModels[NB_BRIDGE_U_MODELS];
Model bridgeLModels[NB_BRIDGE_L_MODELS];
Model bridgeIModels[NB_BRIDGE_I_MODELS];
Model bridgeEndModels[NB_BRIDGE_END_MODELS];
Model bridgeNoneModels[NB_BRIDGE_NONE_MODELS];
Model fenceModels[NB_FENCE_MODELS];
Model cloudModels[NB_CLOUD_MODELS];
Model playerModels[NB_PLAYER_MODELS];

// Getters
Model *getLandModels() {
    return landModels;
}

Model *getWaterModels() {
    return waterModels;
}

Model *getBridgeXModels() {
    return bridgeXModels;
}

Model *getBridgeUModels() {
    return bridgeUModels;
}

Model *getBridgeLModels() {
    return bridgeLModels;
}

Model *getBridgeIModels() {
    return bridgeIModels;
}

Model *getBridgeEndModels() {
    return bridgeEndModels;
}

Model *getBridgeNoneModels() {
    return bridgeNoneModels;
}

Model *getFenceModels() {
    return fenceModels;
}

Model *getCloudModels() {
    return cloudModels;
}

Model *getPlayerModels() {
    return playerModels;
}

// Loading and unloading
void loadLandModels(Shader shadowShader) {
    for (int i = 0; i < NB_LAND_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/surfaces/land/land_%d.obj", i + 1);
        landModels[i] = LoadModel(modelName);
        landModels[i].materials[0].shader = shadowShader;
    }
}

void unloadLandModels() {
    for (int i = 0; i < NB_LAND_MODELS; i++) {
        UnloadModel(landModels[i]);
    }
}

void loadWaterModels(Shader shadowShader) {
    for (int i = 0; i < NB_WATER_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/surfaces/water/water_%d.obj", i + 1);
        waterModels[i] = LoadModel(modelName);
        waterModels[i].materials[0].shader = shadowShader;
    }
}

void unloadWaterModels() {
    for (int i = 0; i < NB_WATER_MODELS; i++) {
        UnloadModel(waterModels[i]);
    }
}

void loadBridgeXModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_X_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridges_x/bridge_x_%d.obj", i + 1);
        bridgeXModels[i] = LoadModel(modelName);
        bridgeXModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeXModels() {
    for (int i = 0; i < NB_BRIDGE_X_MODELS; i++) {
        UnloadModel(bridgeXModels[i]);
    }
}

void loadBridgeUModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_U_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridges_u/bridge_u_%d.obj", i + 1);
        bridgeUModels[i] = LoadModel(modelName);
        bridgeUModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeUModels() {
    for (int i = 0; i < NB_BRIDGE_U_MODELS; i++) {
        UnloadModel(bridgeUModels[i]);
    }
}

void loadBridgeLModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_L_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridges_l/bridge_l_%d.obj", i + 1);
        bridgeLModels[i] = LoadModel(modelName);
        bridgeLModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeLModels() {
    for (int i = 0; i < NB_BRIDGE_L_MODELS; i++) {
        UnloadModel(bridgeLModels[i]);
    }
}

void loadBridgeIModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_I_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridges_i/bridge_i_%d.obj", i + 1);
        bridgeIModels[i] = LoadModel(modelName);
        bridgeIModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeIModels() {
    for (int i = 0; i < NB_BRIDGE_I_MODELS; i++) {
        UnloadModel(bridgeIModels[i]);
    }
}

void loadBridgeEndModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_END_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridges_end/bridge_end_%d.obj", i + 1);
        bridgeEndModels[i] = LoadModel(modelName);
        bridgeEndModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeEndModels() {
    for (int i = 0; i < NB_BRIDGE_END_MODELS; i++) {
        UnloadModel(bridgeEndModels[i]);
    }
}

void loadBridgeNoneModels(Shader shadowShader) {
    for (int i = 0; i < NB_BRIDGE_NONE_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridges_none/bridge_none_%d.obj", i + 1);
        bridgeNoneModels[i] = LoadModel(modelName);
        bridgeNoneModels[i].materials[0].shader = shadowShader;
    }
}

void unloadBridgeNoneModels() {
    for (int i = 0; i < NB_BRIDGE_NONE_MODELS; i++) {
        UnloadModel(bridgeNoneModels[i]);
    }
}

void loadFenceModels(Shader shadowShader) {
    for (int i = 0; i < NB_FENCE_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/fences/fence_%d.obj", i + 1);
        fenceModels[i] = LoadModel(modelName);
        fenceModels[i].materials[0].shader = shadowShader;
    }
}

void unloadFenceModels() {
    for (int i = 0; i < NB_FENCE_MODELS; i++) {
        UnloadModel(fenceModels[i]);
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
    loadLandModels(shadowShader);
    loadWaterModels(shadowShader);
    loadBridgeXModels(shadowShader);
    loadBridgeUModels(shadowShader);
    loadBridgeLModels(shadowShader);
    loadBridgeIModels(shadowShader);
    loadBridgeEndModels(shadowShader);
    loadBridgeNoneModels(shadowShader);
    loadFenceModels(shadowShader);
    loadCloudModels(shadowShader);
    loadPlayerModels(shadowShader);
}

void unloadModels() {
    unloadLandModels();
    unloadWaterModels();
    unloadBridgeXModels();
    unloadBridgeUModels();
    unloadBridgeLModels();
    unloadBridgeIModels();
    unloadBridgeEndModels();
    unloadBridgeNoneModels();
    unloadFenceModels();
    unloadCloudModels();
    unloadPlayerModels();
}

void assignSurfaceModel(Tile *tile) {
    if (tile->land)
        tile->modelGroup.surface = &landModels[rand() % NB_LAND_MODELS];
    else
        tile->modelGroup.surface = &waterModels[rand() % NB_WATER_MODELS];
}

void assignBridgeModel(Tile *tile) {
    bool northBridge = tile->path.north;
    bool eastBridge = tile->path.east;
    bool southBridge = tile->path.south;
    bool westBridge = tile->path.west;
    int nbBridge = 0;
    if (northBridge) nbBridge++;
    if (eastBridge) nbBridge++;
    if (southBridge) nbBridge++;
    if (westBridge) nbBridge++;
    if (nbBridge == 4) {
        tile->modelGroup.bridge = &bridgeXModels[rand() % NB_BRIDGE_X_MODELS];
        tile->bridgeRotation = rand() % 4 * 90;
    }
    else if (nbBridge == 0 ) {
        tile->modelGroup.bridge = &bridgeNoneModels[rand() % NB_BRIDGE_NONE_MODELS];
        tile->bridgeRotation = rand() % 4 * 90;
    }
    else if (nbBridge == 3) {
        tile->modelGroup.bridge = &bridgeUModels[rand() % NB_BRIDGE_U_MODELS];
        if (!northBridge) {
            tile->bridgeRotation = 180;
            return;
        }
        if (!eastBridge) {
            tile->bridgeRotation = 90;
            return;
        }
        if (!southBridge) {
            tile->bridgeRotation = 0;
            return;
        }
        if (!westBridge) {
            tile->bridgeRotation = -90;
            return;
        }
    }
    else if (nbBridge == 2) {
        if (northBridge && southBridge) {
            tile->modelGroup.bridge = &bridgeIModels[rand() % NB_BRIDGE_I_MODELS];
            tile->bridgeRotation = rand() % 2 * 180 + 90;
        }
        else if (eastBridge && westBridge) {
            tile->modelGroup.bridge = &bridgeIModels[rand() % NB_BRIDGE_I_MODELS];
            tile->bridgeRotation = rand() % 2 * 180;
        }
        else {
            tile->modelGroup.bridge = &bridgeLModels[rand() % NB_BRIDGE_L_MODELS];
            if (northBridge && eastBridge) {
                tile->bridgeRotation = 0;
                return;
            }
            if (eastBridge && southBridge) {
                tile->bridgeRotation = -90;
                return;
            }
            if (southBridge && westBridge) {
                tile->bridgeRotation = 180;
                return;
            }
            if (westBridge && northBridge) {
                tile->bridgeRotation = 90;
                return;
            }
        }
    }
    else if (nbBridge == 1) {
        tile->modelGroup.bridge = &bridgeEndModels[rand() % NB_BRIDGE_END_MODELS];
        if (northBridge) {
            tile->bridgeRotation = 0;
            return;
        }
        if (eastBridge) {
            tile->bridgeRotation = -90;
            return;
        }
        if (southBridge) {
            tile->bridgeRotation = 180;
            return;
        }
        if (westBridge) {
            tile->bridgeRotation = 90;
            return;
        }
    }
    else {
        printf("Invalid Bridge tile\n");
    }
}

void assignFenceModels(Tile *tile) {
    tile->modelGroup.northFence = &fenceModels[rand() % NB_FENCE_MODELS];
    tile->modelGroup.eastFence = &fenceModels[rand() % NB_FENCE_MODELS];
    tile->modelGroup.southFence = &fenceModels[rand() % NB_FENCE_MODELS];
    tile->modelGroup.westFence = &fenceModels[rand() % NB_FENCE_MODELS];
}
