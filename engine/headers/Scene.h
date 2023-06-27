#ifndef SCENE_H
#define SCENE_H
#pragma once
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct SceneObject;

class Scene
{
    public:
        int tileIndex;
        std::vector<SceneObject*> objs;

        void init(std::string sceneFile);
};

#endif