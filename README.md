# _**Aengine**_ project template

This is a **Aengine** project template to easily get started.

You can refactor anything how you want it to be but you have to be careful with the **_#includes_**.

The _**main.h**_ file (where you write code and logic) looks like this

``` cpp
#pragma once
#include "raylib.h"
#include "../engine/headers/engine.h"

// define variables here...

void tileCheck(TileMap* tileMap)
{
    assert(0);
}

// ...or here

// called once at start of program
void start() 
{  
    
}

// called every frame
void update()
{
    
}

// render every frame
void render()
{
    ClearBackground(CORNFLOWER);
    DrawText("Hello world!", 100, 200, 30, MAROON);
}

// dispose textures, audio, etc..
void dispose()
{
    
}
```

The _**tileCheck(TileMap* tileMap)**_ function can be used to check what tiles are at which index of a 2D array, the size of the 2D array can be changed in macros of the _**config.h**_ file located in _engine/headers_.

Example:
``` cpp

if (getTile(tileMap) == 1)
{
    // tile position: tileMap->y * tileMap * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y
    // dirt tile at position
}
else if (getTile(tileMap) == 2)
{
    // tile position: tileMap->y * tileMap * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y
    // grass tile at position
}
else if (getTile(tileMap) == 3)
{
    // tile position: tileMap->y * tileMap * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y
    // stone tile at position
}

```

In this case:
``` cpp
void tileCheck(TileMap* tileMap)
{
    assert(0);
}
```
the function just doesn't do anything