#include "types.h"
#include "backend.h"
#include "movement.h"
#include "drawing.h"
#include <time.h>
#include <raylib.h>
#include <stdlib.h>

#define GRID_WIDTH 13
#define GRID_HEIGHT 9

int main() {
    // Init
    Color backgroundColor = (Color){0, 139, 255};
    windowSetup(backgroundColor);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    srand(time(NULL));
    float timerCollapse = 0.0f;
    float timerCircleOverlay = 0.0f;
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int playerX = GRID_WIDTH / 2;
    int playerY = GRID_HEIGHT / 2;
    float circleOverlayRadius = GetScreenHeight() / 4.;

    // Camera
    float targetDistance = 35.;
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    camera.target = (Vector3){6.0f, 0.0f, 4.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 20.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Grid
    Grid *grid = makeGrid(GRID_WIDTH, GRID_HEIGHT);
    // temp
    for (int i = 0; i < grid->nbTiles; i++) {
        collapseOneTile(grid);
    }

    // Loop
    while (!WindowShouldClose()) {
        // Resize
        if (IsWindowResized()) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }

        timerCollapse += GetFrameTime();
        if (timerCollapse >= 0.01f && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            collapseOneTile(grid);
            timerCollapse = 0.0f;
        }

        executeControls(grid, &playerX, &playerY, &camera);

        timerCircleOverlay += GetFrameTime();
        int newMouseX = GetMouseX();
        int newMouseY = GetMouseY();
        if (newMouseX != mouseX || newMouseY != mouseY) {
            timerCircleOverlay = 0.0f;
            mouseX = newMouseX;
            mouseY = newMouseY;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            uncollapseMouseTiles(grid, camera, circleOverlayRadius, playerX, playerY);
            timerCircleOverlay = 0.0f;
        }

        // Camera
        updateCamera(&camera, &targetDistance);

        // Drawing
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(backgroundColor);
        drawGrid(grid);
        drawPlayer(playerX, playerY);
        EndMode3D();
        if (timerCircleOverlay <= 2.)
            drawCircleOverlay(circleOverlayRadius);
        EndDrawing();
    }
    CloseWindow();

    // De-init
    freeGrid(grid);
    return 0;
}
