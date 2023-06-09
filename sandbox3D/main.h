#pragma once
#include "../engine/headers/engine.h"
#include "raylib.h"
#include "math.h"
#include "raymath.h"
#include "string"

Console console;

PerspectiveCamera camera;
float cameraSpeed;
float sensitivity;
bool isMouseLocked;

Vector2 velocity;
float gravity;
float jumpForce;

Texture2D cubeTex;
Texture2D cubeTex2;
Texture2D weaponTex;
Texture2D crosshair;
Texture2D wallTex1;
Texture2D wallTex2;
Texture2D cacoTex;

Vector3 cacoPos;
float cacoSpeed;

Model scientist;

void start()
{
    SetExitKey(KEY_NULL);
    camera.position = {0, 100, 10};
    camera.target = {0, 0, 0};
    camera.up = {0, 1, 0};
    camera.fov = 60;
    camera.matrix.projection = CAMERA_PERSPECTIVE;
    camera.front = {0, 0, -1};
    sensitivity = 0.1f;
    isMouseLocked = false;

    velocity = {0};
    velocity.x = 5;
    gravity = 100;
    jumpForce = 25;

    cacoPos = {-5, 1, 8};
    cacoSpeed = 1.5f;

    cubeTex = LoadTexture("../assets/wall.png");
    cubeTex2 = LoadTexture("../assets/wallS.png");
    weaponTex = LoadTexture("../assets/weapon.png");
    crosshair = LoadTexture("../assets/crosshair.png");
    wallTex1 = LoadTexture("../assets/doom1.png");
    wallTex2 = LoadTexture("../assets/wolf1.png");
    cacoTex = LoadTexture("../assets/cacodemon.png");

    scientist = LoadModel("../assets/models/scientist.glb");
    scientist.transform = MatrixRotateX(DEG2RAD * 90.0f);
}

void update()
{
    console.update();

    if (IsKeyPressed(KEY_ESCAPE))
        isMouseLocked = !isMouseLocked;

    camera.update();
    camera.SetFirstPerson(sensitivity, isMouseLocked);
    camera.SetDefaultFPSControls(KEY_W, KEY_S, KEY_A, KEY_D, velocity.x, isMouseLocked);

    camera.position.y += velocity.y * GetFrameTime();

    velocity.y -= gravity * GetFrameTime();
    if (velocity.y >= 500) velocity.y = 500;

    if (camera.position.y <= 1)
    {
        camera.position.y = 1;
        if (IsKeyPressed(KEY_SPACE) && isMouseLocked)
            velocity.y = jumpForce;  
    }

    if (camera.position.x > cacoPos.x)
        cacoPos.x += cacoSpeed * GetFrameTime();
    if (camera.position.x < cacoPos.x)
        cacoPos.x -= cacoSpeed * GetFrameTime();
    if (camera.position.z > cacoPos.z)
        cacoPos.z += cacoSpeed * GetFrameTime();
    if (camera.position.z < cacoPos.z)
        cacoPos.z -= cacoSpeed * GetFrameTime();

    // if (IsKeyDown(KEY_SPACE) && isMouseLocked)
    //     camera.position.y += cameraSpeed * GetFrameTime();
    // if (IsKeyDown(KEY_LEFT_CONTROL) && isMouseLocked)
    //     camera.position.y -= cameraSpeed * GetFrameTime();

    camera.DefaultFPSMatrix();
}

void render()
{
    BeginMode3D(camera.matrix);
    ClearBackground(CORNFLOWER);

    DrawCube({0, 1, 0}, 2, 2, 2, MAROON);

    DrawCubeTexture(cubeTex2, {5, 1, 4}, 2, 2, 2, WHITE);
    DrawCubeTextureRec(cubeTex, (Rectangle){ 0, cubeTex.height/2.0f, cubeTex.width/2.0f, cubeTex.height/2.0f }, (Vector3){ 2.0f, 1.0f, 0.0f }, 2.0f, 2.0f, 2.0f, WHITE);
    DrawCubeTextureRec(cubeTex, (Rectangle){ 0, (float) cubeTex.height, (float) cubeTex.width, (float) cubeTex.height }, (Vector3){ 5.0f, 1.0f, 10.0f }, 4.0f, 1.0f, 3.0f, WHITE);

    DrawCubeTexture(wallTex1, {-5, 1, 4}, 2, 2, 2, WHITE);
    DrawCubeTexture(wallTex2, {-3, 1, 4}, 2, 2, 2, WHITE);

    DrawModel(scientist, {-5, 1, 4}, 0.05f, WHITE);

    DrawTexture3D(cacoTex, cacoPos, 2, 2, 2, -(atan2(camera.position.z - 8, camera.position.x + 5)*RAD2DEG - 90), WHITE);

    DrawGrid(100, 1);

    EndMode3D();
    DrawTextureEx(weaponTex, {GetScreenWidth() - (float)weaponTex.width*4, GetScreenHeight() - (float)weaponTex.height*4}, 0, 4, WHITE);
    DrawTextureEx(crosshair, {(float)(GetScreenWidth()/2 - crosshair.width), (float)(GetScreenHeight()/2 - crosshair.height)}, 0, 2, WHITE);

    DrawText(TextFormat("Pos: %.2f, %.2f, %.2f", camera.position.x, camera.position.y, camera.position.z), 10, 10, 30, WHITE);
    DrawText(TextFormat("Vel: %.2f, %.2f", velocity.x, velocity.y), 10, 35, 30, WHITE);
    console.render();
}

void dispose()
{

}
