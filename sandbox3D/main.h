#pragma once
#include "../engine/headers/engine.h"
#include "raylib.h"

#define PLAYER_MOVEMENT_SPEED 10.0f
#define PLAYER_MOUSE_SENSITIVITY 0.2f

Console console;
Camera3D camera;
Model map;
Vector3 cameraDirection;
float gravity;

void start()
{
    SetExitKey(KEY_NULL);
    camera = {0};
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetCameraMoveControls(KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL);
    DisableCursor(); // Limit cursor to relative movement inside the window

    map = LoadModel("assets/dust2.glb");
    cameraDirection = normalizeV3(subV3(camera.target, camera.position));

    gravity = 800;
}

void update()
{
    console.update();
    UpdateCamera(&camera);
    cameraDirection = normalizeV3(subV3(camera.target, camera.position));
    
    camera.position.y -= gravity * GetFrameTime();
    if (camera.position.y <= 2.0f) camera.position.y = 2.0f;

    if (IsKeyDown(KEY_W))
    {
        camera.position = addV3(camera.position, scaleV3(cameraDirection, 0.05f));
    }
    if (IsKeyDown(KEY_S))
    {
        camera.position = subV3(camera.position, scaleV3(cameraDirection, 0.05f));
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        camera.position.y = 800;
    }
}

void render()
{
    ClearBackground(CORNFLOWER);
    BeginMode3D(camera);

    DrawCube((Vector3){0, 1, 0}, 1, 1, 1, GREEN);
    DrawCube((Vector3){2, 1, 0}, 1, 1, 1, BLUE);
    DrawCube((Vector3){0, 1, 2}, 1, 1, 1, RED);
    DrawModelEx(map, (Vector3){-20, 0, 0}, (Vector3){1, 0, 0}, -180, (Vector3){0.035f, 0.035f, 0.035f}, WHITE);
    DrawGrid(10, 1.0f);

    EndMode3D();
    console.render();
}

void dispose()
{

}