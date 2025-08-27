#include "structures.h"
#include "models.h"
#include "backend.h"
#include "movement.h"
#include "drawing.h"
#include <time.h>
#include <raylib.h>
#include <stdlib.h>

#define GRID_WIDTH 13
#define GRID_HEIGHT 9

float min(float a, float b) {
    return a < b ? a : b;
}

int main() {
    // Init
    Color backgroundColor = (Color){255, 255, 255};
    windowSetup(backgroundColor);
    HideCursor();
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    srand(time(NULL));
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    int playerX = GRID_WIDTH / 2;
    int playerY = GRID_HEIGHT / 2;
    float playerXPrev = (float) playerX;
    float playerYPrev = (float) playerY;
    float playerXRender = playerXPrev;
    float playerYRender = playerYPrev;
    bool playerIsMoving = false;
    float circleOverlayRadius = GetScreenHeight() / 6.;
    loadModels();

    // Camera
    float targetDistance = 35.;
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    camera.target = (Vector3){6.0f, 0.0f, 4.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 20.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Timers
    float timerCollapse = 0.;
    float timerCircleOverlay = 0.;
    float timerMovement = 0.;

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
            circleOverlayRadius = GetScreenHeight() / 6.;
        }

        timerCollapse += GetFrameTime();
        timerCircleOverlay += GetFrameTime();
        timerMovement += GetFrameTime();

        if (timerCollapse >= 0.02 && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            collapseOneTile(grid);
            timerCollapse = 0.;
        }

        if (timerMovement >= 0.5) {
            playerXPrev = (float) playerX;
            playerYPrev = (float) playerY;
            playerXRender = playerXPrev;
            playerYRender = playerYPrev;
            camera.target.x = playerXRender;
            camera.target.z = playerYRender;
            executeControls(grid, &playerX, &playerY, &timerMovement);
            playerXRender = (float) playerXPrev;
            playerYRender = (float) playerYPrev;
        }
        else { // moving
            float t = timerMovement / 0.5f;  // 0 → 1 over 0.5s
            playerXRender = playerXPrev + ((float) playerX - playerXPrev) * t;
            playerYRender = playerYPrev + ((float) playerY - playerYPrev) * t;
            camera.target.x = playerXRender;
            camera.target.z = playerYRender;
        }

        int newMouseX = GetMouseX();
        int newMouseY = GetMouseY();
        if (newMouseX != mouseX || newMouseY != mouseY) {
            timerCircleOverlay = 0.;
            mouseX = newMouseX;
            mouseY = newMouseY;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            uncollapseMouseTiles(grid, camera, circleOverlayRadius, playerX, playerY);
            timerCircleOverlay = 0.;
        }

        // Camera
        updateCamera(&camera, &targetDistance);

        // Drawing
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(backgroundColor);
        drawGrid(grid);
        drawPlayer(playerXRender, playerYRender);
        EndMode3D();
        if (timerCircleOverlay <= 2.)
            drawCircleOverlay(circleOverlayRadius);
        EndDrawing();
    }
    unloadModels();
    CloseWindow();

    // De-init
    freeGrid(grid);
    return 0;
 }
