#ifndef LOADSCENE_H
#define LOADSCENE_H
#pragma once
#include "iostream"
#include "stdio.h"
#include "stdlib.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Scene.h"

struct SceneObject
{
    Vector3 pos;
    Vector3 scale;
    Vector3 rot;
    int id;
};

std::vector<SceneObject*> loadSceneFile(std::string& filename)
{
    std::vector<SceneObject*> objs;
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file." << std::endl;
        return objs;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        SceneObject* obj = new SceneObject;
        std::istringstream iss(line);
        std::string token;

        while (iss >> token) {
            if (token == "x:") {
                iss >> obj->pos.x;
            } else if (token == "y:") {
                iss >> obj->pos.y;
            } else if (token == "z:") {
                iss >> obj->pos.z;
            } else if (token == "w:") {
                iss >> obj->scale.x;
            } else if (token == "h:") {
                iss >> obj->scale.y;
            } else if (token == "d:") {
                iss >> obj->scale.z;
            } else if (token == "rx:") {
                iss >> obj->rot.x;
            } else if (token == "ry:") {
                iss >> obj->rot.y;
            } else if (token == "rz:") {
                iss >> obj->rot.z;
            } else if (token == "id:") {
                iss >> obj->id;
            }
        }

        objs.push_back(obj);
    }

    inputFile.close();
    return objs;
}

void idCheck(Scene* scene);

SceneObject* getObjectById(int id, Scene* scene)
{
    for (SceneObject* obj : scene->objs)
    {
        if (obj->id == id)
        {
            return obj;
        }
    }

    return 0;
}

SceneObject* getObject(Scene* scene)
{
    return scene->objs[scene->tileIndex];
}

#endif