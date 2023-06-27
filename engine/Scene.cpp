#include "headers/LoadScene.h"
#include "headers/Scene.h"

void Scene::init(std::string sceneFile)
{
    this->objs = loadSceneFile(sceneFile);
    for (this->tileIndex = 0; this->tileIndex < (int) this->objs.size(); this->tileIndex++)
    {
        idCheck(this);
    }
    
}