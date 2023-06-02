#include "headers/EntityManager.h"
#include "headers/toolbox.h"
#include "headers/Entity.h"
#include "headers/Collider.h"
#include "headers/QuadTree.h"
#include "headers/Component.h"
#include "headers/StaticBody.h"
#include "headers/RigidBody.h"

bool compareEntities(Entity* e1, Entity* e2)
{
   return e1->getZ() < e2->getZ();
}

void sortEntitiesByZIndex(std::vector<Entity*>& entities)
{
   std::sort(entities.begin(), entities.end(), compareEntities);
}

QuadTree EntityManager::quadtree(0, {0, 0, 10000, 10000});
std::vector<Entity*> EntityManager::entities;
Camera2D EntityManager::camera;
bool EntityManager::useCamera;
bool EntityManager::renderCollidersBool = false;
bool EntityManager::debugBool = false;
b2Vec2 EntityManager::gravity(0.0f, b2Grav);
b2World EntityManager::world(EntityManager::gravity);

void EntityManager::update()
{
    EntityManager::world.Step(1.0f/float(fps), velocityIterations, positionIterations);

    quadtree.clear();

    for (Entity *entity : EntityManager::entities)
    {
        entity->update();
        quadtree.insert(entity);
    }

    for (Entity* entity : EntityManager::entities)
    {
        if (entity->hasComponent<StaticBody>())
        {
            entity->getComponent<StaticBody>()->collisionCheck();
        }
        else if (entity->hasComponent<RigidBody>())
        {
            entity->getComponent<RigidBody>()->collisionCheck();
        }
    }

    // if (!EntityManager::useCamera)
    // {
    //     for (Entity* entity : EntityManager::entities)
    //     {
    //         entity->update();
    //     }
    // }
    // else 
    // {
    //     for (Entity* entity : EntityManager::entities)
    //     {
    //         if (EntityManager::isInCamera(entity)) entity->update();
    //     }
    // }
}

void EntityManager::setBounds(Rectangle bounds)
{
    EntityManager::quadtree.setBounds(bounds);
}

void EntityManager::setCamera(Camera2D* camera)
{
    EntityManager::camera.offset = camera->offset;
    EntityManager::camera.rotation = camera->rotation;
    EntityManager::camera.target = camera->target;
    EntityManager::camera.zoom = camera->zoom;
    EntityManager::useCamera = true;
}

bool EntityManager::isInCamera(Entity* other)
{
    Rectangle cameraRec = {
        EntityManager::camera.target.x - EntityManager::camera.offset.x,
        EntityManager::camera.target.y - EntityManager::camera.offset.y,
        (float)GetScreenWidth(),
        (float)GetScreenHeight()
    };
    return CheckCollisionRecs({other->pos.x, other->pos.y, other->scale.x, other->scale.y}, cameraRec);
}

void EntityManager::sortEntities()
{
    sortEntitiesByZIndex(EntityManager::entities);
}

void EntityManager::render()
{
    std::vector<Entity*> renderCalls = EntityManager::quadtree.retrieve({EntityManager::camera.target.x - EntityManager::camera.offset.x, EntityManager::camera.target.y - EntityManager::camera.offset.y, (float)GetScreenWidth(), (float)GetScreenHeight()});
    for (Entity *entity : renderCalls)
    {
        if (EntityManager::isInCamera(entity))
        {
            entity->render();
        }
    }
    if (EntityManager::renderCollidersBool)
    {
        EntityManager::renderColliders(EntityManager::debugBool);
    }
}

void EntityManager::renderColliders(bool debugMode)
{
    if (!EntityManager::useCamera)
    {
        for (Entity* entity : EntityManager::entities)
        {
            if (entity->hasComponent<Object>())
            {
                entity->getComponent<Object>()->renderColliders();
            }
            else if (entity->hasComponent<Collider>())
            {
                entity->getComponent<Collider>()->renderColliders();
            }
        }
    }
    else 
    {
        if (debugMode)
        {
            Rectangle cameraRec = {
                EntityManager::camera.target.x - EntityManager::camera.offset.x,
                EntityManager::camera.target.y - EntityManager::camera.offset.y,
                (float)GetScreenWidth(),
                (float)GetScreenHeight()
            };
            DrawRectangleLinesEx(cameraRec, 1, colliderColor);
            DrawCircleLines(EntityManager::camera.target.x + EntityManager::camera.offset.x, EntityManager::camera.target.y + EntityManager::camera.offset.y, 2.5f, colliderColor);
        }
        for (Entity* entity : EntityManager::entities)
        {
            if (entity->hasComponent<Object>())
            {
                if (debugMode) 
                    DrawLineV(entity->pos, {(EntityManager::camera.target.x - EntityManager::camera.offset.x) + GetScreenWidth()/2.0f, (EntityManager::camera.target.y - EntityManager::camera.offset.y) + GetScreenHeight()/2.0f}, colliderColor);
                if (EntityManager::isInCamera(entity)) entity->getComponent<Object>()->renderColliders();
            }
            else if (entity->hasComponent<Collider>())
            {
                if (debugMode) 
                    DrawLineV(entity->pos, {(EntityManager::camera.target.x - EntityManager::camera.offset.x) + GetScreenWidth()/2.0f, (EntityManager::camera.target.y - EntityManager::camera.offset.y) + GetScreenHeight()/2.0f}, colliderColor);
                if (EntityManager::isInCamera(entity)) entity->getComponent<Collider>()->renderColliders();
            }
        }
    }

}

void EntityManager::dispose()
{
    for (Entity* entity : EntityManager::entities)
    {
        entity->dispose();
        delete entity;
        EntityManager::kill(entity);
    }
}

void EntityManager::kill(Entity* entity)
{
    for (auto it = EntityManager::entities.begin(); it != EntityManager::entities.end(); ++it)
    {
        if (*it == entity)
        {
            EntityManager::entities.erase(it);
            break;
        }
    }
}

template<typename T>
void EntityManager::instantiate(T* entity, Vector2 pos, Vector2 scale, float rotation)
{
    entity->pos = pos;
    entity->scale = scale;
    entity->rotation = rotation;
    std::cout << entity->getIndex();
}