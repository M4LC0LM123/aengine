#include "raylib.h"
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#define GUI_GUILAYOUT_IMPLEMENTATION
#include "raygui.h"
#include "../main.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //const int screenWidth = 1024;
    //const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, title);
    start();
    SetTargetFPS(fps);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        update();
        BeginDrawing();
        render();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    dispose();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}