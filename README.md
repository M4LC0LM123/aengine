# aengine

Aengine is a simple "game engine" made in c++ using the raylib library.
It is not as powerful and performant as Unity but it should be useful for beginners.

* It contains: 
    * Box2D physics
    * Custom physics (in development, not recommended for physics based games)
    * Entity Component System that can be customized and still needs some work for some of the default components
    * "Bloom" (just janky lighting that isn't really lighting)
    * Debug Console
    * Simple tilemap loading
    * Prefabs (can be used but still in development)
    * A really simple example of a particle system that isn't really customizeable
    * Orthographic camera with pre built camera controllers
    * misc toolbox functions
    * config file in engine/headers
    * simple scene loading system thats similar to the tilemap system
    * 3d rendering
    * perspective camera also with presets
    * barebones tilemap and scene editor

* Will contain:
    * faster compiling
    * 3d scene editor
    * 3d physics and collision detection
    * a real lighting system
    * minecraft/terraria-style lighting system
    * easier and more automatic web building than building normal raylib games