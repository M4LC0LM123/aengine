#pragma once
#include "../engine/headers/engine.h"
#include "raylib.h"
#include "math.h"

Console console;


void start()
{

}

void update()
{
    console.update();
}

void render()
{
    ClearBackground(CORNFLOWER);

    console.render();
}

void dispose()
{

}
