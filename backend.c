#include "backend.h"
#include "structures.h"
#include "models.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#define LAND_PROBABILITY 0.5
#define DECORATION_PROBABILITY 0.5
#define PATH_PROBABILITY 0.2

bool randFromProbability(float probability) {
    return (rand() % 100 < 100 * probability);
}

void addTile(Grid *grid, Tile *tile) {
    grid->tiles[grid->nbTiles] = tile;
    grid->nbTiles++;
}

void removeTile(Grid *grid, int posX, int posY) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == posX && tile->posY == posY) {
            int j = i;
            // Shift everything
            grid->nbTiles--;
            while (j < grid->nbTiles) {
                grid->tiles[j] = grid->tiles[j+1];
                j++;
            }
            return;
        }
    }
}

void collapsePlayerTile(Grid *grid, int playerX, int playerY) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == playerX && tile->posY == playerY) {
            tile->collapsed = true;
            tile->land = randFromProbability(LAND_PROBABILITY);
            tile->decoration = randFromProbability(DECORATION_PROBABILITY);
            tile->path.north = true;
            tile->path.east = true;
            tile->path.south = true;
            tile->path.west = true;
            tile->surfaceRotation = rand() % 4 * 90;
            tile->bridgeRotation = rand() % 4 * 90;
            assignSurfaceModel(tile);
            assignBridgeModel(tile);
            assignFenceModels(tile);
            return;
        }
    }
}

void collapseTile(Grid *grid, int posX, int posY) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == posX && tile->posY == posY) {
            tile->collapsed = true;
            tile->land = randFromProbability(LAND_PROBABILITY);
            tile->decoration = randFromProbability(DECORATION_PROBABILITY);
            bool foundNorth = false;
            bool foundEast = false;
            bool foundSouth = false;
            bool foundWest = false;
            for (int j = 0; j < grid->nbTiles; j++) {
                Tile *otherTile = grid->tiles[j];
                if (!otherTile->collapsed)
                    continue;
                // North
                if (otherTile->posX == tile->posX && otherTile->posY == tile->posY - 1) {
                    tile->path.north = otherTile->path.south;
                    foundNorth = true;
                }
                // East
                if (otherTile->posX == tile->posX + 1 && otherTile->posY == tile->posY) {
                    tile->path.east = otherTile->path.west;
                    foundEast = true;
                }
                // South
                if (otherTile->posX == tile->posX && otherTile->posY == tile->posY + 1) {
                    tile->path.south = otherTile->path.north;
                    foundSouth = true;
                }
                // West
                if (otherTile->posX == tile->posX - 1 && otherTile->posY == tile->posY) {
                    tile->path.west = otherTile->path.east;
                    foundWest = true;
                }
            }
            if (!foundNorth)
                tile->path.north = randFromProbability(PATH_PROBABILITY);
            if (!foundEast)
                tile->path.east = randFromProbability(PATH_PROBABILITY);
            if (!foundSouth)
                tile->path.south = randFromProbability(PATH_PROBABILITY);
            if (!foundWest)
                tile->path.west = randFromProbability(PATH_PROBABILITY);
            tile->surfaceRotation = rand() % 4 * 90;
            tile->bridgeRotation = rand() % 4 * 90;
            assignSurfaceModel(tile);
            assignBridgeModel(tile);
            assignFenceModels(tile);
            return;
        }
    }
}

void uncollapseTile(Tile *tile) {
    tile->collapsed = false;
    tile->path.north = false;
    tile->path.east = false;
    tile->path.south = false;
    tile->path.west = false;
    tile->surfaceRotation = 0;
    tile->bridgeRotation = 0;
    return;
}

int countCollapsedNeighbors(Grid *grid, int posX, int posY) {
    int nbCollapsedNeighbors = 0;
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (!tile->collapsed)
            continue;
        if (tile->posX == posX && tile->posY == posY - 1) {
            nbCollapsedNeighbors++;
        }
        if (tile->posX == posX && tile->posY == posY + 1) {
            nbCollapsedNeighbors++;
        }
        if (tile->posX == posX - 1 && tile->posY == posY) {
            nbCollapsedNeighbors++;
        }
        if (tile->posX == posX + 1 && tile->posY == posY) {
            nbCollapsedNeighbors++;
        }
    }
    return nbCollapsedNeighbors;
}

void collapseOneTile(Grid *grid) {
    // If everything is collapsed then don't do anything
    int nbUncollapsed = 0;
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (!tile->collapsed)
            nbUncollapsed++;
    }
    if (nbUncollapsed == 0)
        return;
    // Count collapsed neighbors for the whole grid
    int *nbGridCollapsedNeighbors = malloc(grid->nbTiles * sizeof(int));
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->collapsed) {
            nbGridCollapsedNeighbors[i] = -1;
            continue;
        }
        nbGridCollapsedNeighbors[i] = countCollapsedNeighbors(grid, tile->posX, tile->posY);
    }
    // Find a list of collapsable tiles and pick a random one
    int *possibleTilesIndexes = malloc(grid->nbTiles * sizeof(int));
    int nbPossibleTiles = 0;
    for (int n = 4; n >= 0; n--) {
        for (int i = 0; i < grid->nbTiles; i++) {
            if (nbGridCollapsedNeighbors[i] == n) {
                possibleTilesIndexes[nbPossibleTiles] = i;
                nbPossibleTiles++;
            }
        }
        if (nbPossibleTiles > 0) {
            Tile *resultTile = grid->tiles[possibleTilesIndexes[rand() % nbPossibleTiles]];
            collapseTile(grid, resultTile->posX, resultTile->posY);
            return;
        }
    }
    free(possibleTilesIndexes);
    free(nbGridCollapsedNeighbors);
}

void uncollapseMouseTiles(Grid *grid, Camera3D camera, float circleRadius, int playerX, int playerY, Sound soundRemoveTile) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        int tileX = tile->posX;
        int tileY = tile->posY;
        if (tileX == playerX && tileY == playerY)
            continue;
        Vector2 tileCenterScreen = GetWorldToScreen((Vector3) {(float) tileX, 0.0f, (float) tileY}, camera);
        bool flagRemovedTiles = false;
        if (CheckCollisionPointCircle(tileCenterScreen, GetMousePosition(), circleRadius)) {
            for (int i = 0; i < grid->nbTiles; i++) {
                Tile *tile = grid->tiles[i];
                if (tile->collapsed && tile->posX == tileX && tile->posY == tileY) {
                    flagRemovedTiles = true;
                    uncollapseTile(tile);
                }
            }
        }
        if (flagRemovedTiles)
            PlaySound(soundRemoveTile);
    }
}
