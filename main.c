#include "structures.h"
#include "models.h"
#include "backend.h"
#include "movement.h"
#include "drawing.h"
#include <time.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdlib.h>

#define GRID_WIDTH 13
#define GRID_HEIGHT 9
#define SHADOWMAP_RESOLUTION 4096

float min(float a, float b) {
    return a < b ? a : b;
}

RenderTexture2D LoadShadowmapRenderTexture(int width, int height) {
    RenderTexture2D target = { 0 };

    target.id = rlLoadFramebuffer(); // Load an empty framebuffer
    target.texture.width = width;
    target.texture.height = height;

    if (target.id > 0) {
        rlEnableFramebuffer(target.id);

        // Create depth texture
        // We don't need a color texture for the shadowmap
        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach depth texture to FBO
        rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

        rlDisableFramebuffer();
    }
    else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}

// Unload shadowmap render texture from GPU memory (VRAM)
void UnloadShadowmapRenderTexture(RenderTexture2D target) {
    if (target.id > 0) {
        // NOTE: Depth texture/renderbuffer is automatically
        // queried and deleted before deleting framebuffer
        rlUnloadFramebuffer(target.id);
    }
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

    // Init shaders
    Shader shadowShader = LoadShader("shaders/shadows.vs", "shaders/shadows.fs");
    shadowShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shadowShader, "viewPos");
    Vector3 lightDir = Vector3Normalize((Vector3){ 0.35f, -1.0f, -0.35f });
    Color lightColor = (Color) {230, 220, 200};
    Vector4 lightColorNormalized = ColorNormalize(lightColor);
    int lightDirLoc = GetShaderLocation(shadowShader, "lightDir");
    int lightColLoc = GetShaderLocation(shadowShader, "lightColor");
    SetShaderValue(shadowShader, lightDirLoc, &lightDir, SHADER_UNIFORM_VEC3);
    SetShaderValue(shadowShader, lightColLoc, &lightColorNormalized, SHADER_UNIFORM_VEC4);
    int ambientLoc = GetShaderLocation(shadowShader, "ambient");
    float ambient[4] = {2.0, 1.9, 1.7, 1.};
    SetShaderValue(shadowShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
    int lightVPLoc = GetShaderLocation(shadowShader, "lightVP");
    int shadowMapLoc = GetShaderLocation(shadowShader, "shadowMap");
    int shadowMapResolution = SHADOWMAP_RESOLUTION;
    SetShaderValue(shadowShader, GetShaderLocation(shadowShader, "shadowMapResolution"), &shadowMapResolution, SHADER_UNIFORM_INT);
    RenderTexture2D shadowMap = LoadShadowmapRenderTexture(SHADOWMAP_RESOLUTION, SHADOWMAP_RESOLUTION);
    loadModels(shadowShader);

    // Cameras
    float targetDistance = 35.;
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    camera.target = (Vector3){6.0f, 0.0f, 4.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 20.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Camera3D lightCamera = (Camera3D){ 0 };
    lightCamera.position = Vector3Scale(lightDir, -15.0f);
    lightCamera.target = Vector3Zero();
    lightCamera.projection = CAMERA_ORTHOGRAPHIC;
    lightCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    lightCamera.fovy = 20.0f;

    // Timers
    float timerCollapse = 0.;
    float timerCircleOverlay = 0.;
    float timerMovement = 0.;

    // Grid
    Grid *grid = makeGrid(GRID_WIDTH, GRID_HEIGHT);
    collapsePlayerTile(grid,playerX, playerY);

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

        // Movement
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

        // Camera
        updateCamera(&camera, &targetDistance);
        updateLightCamera(&lightCamera, playerXPrev, playerYPrev);

        // Mouse
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

        // Drawing
        BeginDrawing();
            // Record the light matrices for future use!
            Matrix lightView;
            Matrix lightProj;
            BeginTextureMode(shadowMap); //Build shadowmap
                ClearBackground(WHITE);
                BeginMode3D(lightCamera);
                    lightView = rlGetMatrixModelview();
                    lightProj = rlGetMatrixProjection();
                    drawGrid(grid);
                    drawPlayer(playerXRender, playerYRender);
                EndMode3D();
            EndTextureMode();
            Matrix lightViewProj = MatrixMultiply(lightView, lightProj);

            ClearBackground(backgroundColor);
            SetShaderValueMatrix(shadowShader, lightVPLoc, lightViewProj);
            rlEnableShader(shadowShader.id);
            int slot = 10; // Can be anything 0 to 15, but 0 will probably be taken up
            rlActiveTextureSlot(10);
            rlEnableTexture(shadowMap.depth.id);
            rlSetUniform(shadowMapLoc, &slot, SHADER_UNIFORM_INT, 1);

            BeginMode3D(camera);
                drawGrid(grid);
                drawPlayer(playerXRender, playerYRender);
            EndMode3D();
            if (timerCircleOverlay <= 2.)
                drawCircleOverlay(circleOverlayRadius);
        EndDrawing();
    }
    // De-init
    UnloadShader(shadowShader);
    unloadModels();
    UnloadShadowmapRenderTexture(shadowMap);
    CloseWindow();
    freeGrid(grid);
    return 0;
 }
