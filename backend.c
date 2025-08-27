#include "backend.h"
#include "structures.h"
#include "models.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

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

Connection makeRandomConnection() {
    Connection connection = makeConnection();
    if (rand() % 2 == 0)
        connection.bridge = false;
    else
        connection.bridge = true;
    if (rand() % 2 == 0)
        connection.water = false;
    else
        connection.water = true;
    return connection;
}

void collapseTile(Grid *grid, int posX, int posY) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == posX && tile->posY == posY) {
            tile->collapsed = true;
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
                    tile->north = otherTile->south;
                    foundNorth = true;
                }
                // East
                if (otherTile->posX == tile->posX + 1 && otherTile->posY == tile->posY) {
                    tile->east = otherTile->west;
                    foundEast = true;
                }
                // South
                if (otherTile->posX == tile->posX && otherTile->posY == tile->posY + 1) {
                    tile->south = otherTile->north;
                    foundSouth = true;
                }
                // West
                if (otherTile->posX == tile->posX - 1 && otherTile->posY == tile->posY) {
                    tile->west = otherTile->east;
                    foundWest = true;
                }
            }
            if (!foundNorth)
                tile->north = makeRandomConnection();
            if (!foundEast)
                tile->east = makeRandomConnection();
            if (!foundSouth)
                tile->south = makeRandomConnection();
            if (!foundWest)
                tile->west = makeRandomConnection();
            assignBridgeModels(tile);
            assignBridgeCenterModel(tile);
            assignWaterModel(tile);
            return;
        }
    }
}

void uncollapseTile(Grid *grid, int posX, int posY) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        if (tile->posX == posX && tile->posY == posY) {
            tile->collapsed = false;
            tile->north.bridge = false;
            tile->north.water = false;
            tile->east.bridge = false;
            tile->east.water = false;
            tile->south.bridge = false;
            tile->south.water = false;
            tile->west.bridge = false;
            tile->west.water = false;
            tile->modelGroup.waterModelAngle = 0;
            return;
        }
    }
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

void uncollapseMouseTiles(Grid *grid, Camera3D camera, float circleRadius, int playerX, int playerY) {
    for (int i = 0; i < grid->nbTiles; i++) {
        Tile *tile = grid->tiles[i];
        int tileX = tile->posX;
        int tileY = tile->posY;
        if (tileX == playerX && tileY == playerY)
            continue;
        Vector2 tileCenterScreen = GetWorldToScreen((Vector3) {(float) tileX, 0.0f, (float) tileY}, camera);
        if (CheckCollisionPointCircle(tileCenterScreen, GetMousePosition(), circleRadius)) {
            uncollapseTile(grid, tileX, tileY);
        }
    }
}
