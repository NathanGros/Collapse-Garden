#include "types.h"
#include "drawing.h"
#include <raylib.h>
#include <math.h>

// Init

void Init(Color backgroundColor) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1500, 900, "Lakes and Bridges");
    ClearBackground(backgroundColor);
    SetTargetFPS(60);
}

void updateCamera(Camera3D *camera, float *targetDistance) {
    if (IsKeyPressed(KEY_W)) {
        camera->target.z -= 1;
    }
    if (IsKeyPressed(KEY_S)) {
        camera->target.z += 1;
    }
    if (IsKeyPressed(KEY_A)) {
        camera->target.x -= 1;
    }
    if (IsKeyPressed(KEY_D)) {
        camera->target.x += 1;
    }

    // camera zoom
    *targetDistance *= 1. - 0.2 * GetMouseWheelMove();
    if (*targetDistance <= 10.) *targetDistance = 10.;
    if (*targetDistance >= 70.) *targetDistance = 70.;

    // camera position
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float pi = 3.141592;
    float verticalAngle = pi / 3.;
    float horizontalAngle = pi / 2.;
    if (screenHeight > screenWidth) horizontalAngle = pi;
    camera->position.x = camera->target.x + *targetDistance * cos(horizontalAngle) * cos(verticalAngle);
    camera->position.y = camera->target.y + *targetDistance * sin(verticalAngle);
    camera->position.z = camera->target.z + *targetDistance * sin(horizontalAngle) * cos(verticalAngle);
}

// Main

int main() {
    // Init
    Color backgroundColor = (Color){0, 139, 255};
    Init(backgroundColor);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Camera
    float targetDistance = 35.;
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    camera.target = (Vector3){6.0f, 0.0f, 4.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 20.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Grid
    Grid *grid = makeGrid(13, 9);

    // Loop
    while (!WindowShouldClose()) {
        // Resize
        if (IsWindowResized()) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
        }

        // Camera
        updateCamera(&camera, &targetDistance);

        // Drawing
        BeginDrawing();
        BeginMode3D(camera);
        ClearBackground(backgroundColor);
        drawGrid(grid);
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();

    // De-init
    freeGrid(grid);
    return 0;
}
