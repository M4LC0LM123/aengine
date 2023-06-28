#include "headers/LoadScene.h"
#include "headers/Scene.h"

void Scene::init(std::string sceneFile)
{
    this->objs = loadSceneFile(sceneFile);
}