#include "drawing.h"
#include <raylib.h>

void drawGrid(Grid *grid) {
    for (int i = 0; i < grid->width; i++) {
        for (int j = 0; j < grid->height; j++) {
            Tile *tile = grid->tiles[i * grid->height + j];
            Vector3 pos = (Vector3){tile->posX, 0., tile->posY};
            DrawCube(pos, 1., 1., 1., GREEN);
            DrawCubeWires(pos, 1., 1., 1., DARKGREEN);
        }
    }
}
