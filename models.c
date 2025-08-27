#include "models.h"
#include <raylib.h>
#include <stdio.h>

#define NB_BRIDGE_MODELS 1
#define NB_BRIDGE_CENTER_MODELS 1
#define NB_CLOUD_MODELS 1
#define NB_PLAYER_MODELS 1

// load all models
Model bridgeModels[NB_BRIDGE_MODELS];
Model bridgeCenterModels[NB_BRIDGE_CENTER_MODELS];
Model cloudModels[NB_CLOUD_MODELS];
Model playerModels[NB_PLAYER_MODELS];

Model *getBridgeModels() {
    return bridgeModels;
}

Model *getBridgeCenterModels() {
    return bridgeCenterModels;
}

Model *getCloudModels() {
    return cloudModels;
}

Model *getPlayerModels() {
    return playerModels;
}

void loadBridgeModels() {
    for (int i = 0; i < NB_BRIDGE_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridges/bridge_%d.obj", i + 1);
        bridgeModels[i] = LoadModel(modelName);
    }
}

void unloadBridgeModels() {
    for (int i = 0; i < NB_BRIDGE_MODELS; i++) {
        UnloadModel(bridgeModels[i]);
    }
}

void loadBridgeCenterModels() {
    for (int i = 0; i < NB_BRIDGE_CENTER_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/bridge_centers/bridge_center_%d.obj", i + 1);
        bridgeCenterModels[i] = LoadModel(modelName);
    }
}

void unloadBridgeCenterModels() {
    for (int i = 0; i < NB_BRIDGE_CENTER_MODELS; i++) {
        UnloadModel(bridgeCenterModels[i]);
    }
}

void loadCloudModels() {
    for (int i = 0; i < NB_CLOUD_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/clouds/cloud_%d.obj", i + 1);
        cloudModels[i] = LoadModel(modelName);
    }
}

void unloadCloudModels() {
    for (int i = 0; i < NB_CLOUD_MODELS; i++) {
        UnloadModel(cloudModels[i]);
    }
}

void loadPlayerModels() {
    for (int i = 0; i < NB_PLAYER_MODELS; i++) {
        char modelName[100];
        sprintf(modelName, "assets/players/player_%d.obj", i + 1);
        playerModels[i] = LoadModel(modelName);
    }
}

void unloadPlayerModels() {
    for (int i = 0; i < NB_PLAYER_MODELS; i++) {
        UnloadModel(playerModels[i]);
    }
}

void loadModels() {
    loadBridgeModels();
    loadBridgeCenterModels();
    loadCloudModels();
    loadPlayerModels();
}

void unloadModels() {
    unloadBridgeModels();
    unloadBridgeCenterModels();
    unloadCloudModels();
    unloadPlayerModels();
}
