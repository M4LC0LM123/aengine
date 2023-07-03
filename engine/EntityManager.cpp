#include "raylib.h"
#include "headers/EntityManager.h"
#include "headers/toolbox.h"
#include "headers/Entity.h"
#include "headers/Collider.h"
#include "headers/OcTree.h"
#include "headers/Component.h"
#include "headers/StaticBody.h"
#include "headers/RigidBody.h"

bool compareEntities(Entity* e1, Entity* e2)
{
   return e1->pos.z < e2->pos.z;
}

void sortEntitiesByZIndex(std::vector<Entity*>& entities)
{
   std::sort(entities.begin(), entities.end(), compareEntities);
}

QuadTree EntityManager::tree(0, {0, 0, 10000, 10000});
std::vector<Entity*> EntityManager::entities;
Camera2D EntityManager::camera;
bool EntityManager::useCamera;
bool EntityManager::renderCollidersBool = false;
bool EntityManager::debugBool = false;
b2Vec2 EntityManager::gravity(0.0f, b2Grav);
b2World EntityManager::world(EntityManager::gravity);
rp3d::PhysicsWorld::WorldSettings EntityManager::settings;
rp3d::PhysicsCommon EntityManager::physicsCommon;
rp3d::PhysicsWorld* EntityManager::world3D = EntityManager::physicsCommon.createPhysicsWorld(EntityManager::settings);

void EntityManager::init()
{
    EntityManager::settings.defaultVelocitySolverNbIterations = 20; 
    EntityManager::settings.isSleepingEnabled = false; 
    EntityManager::settings.gravity = rp3d::Vector3(0, grav3D, 0); 

    EntityManager::world3D = physicsCommon.createPhysicsWorld(EntityManager::settings);
    EntityManager::world3D->setNbIterationsVelocitySolver(velocityIterations3D); 
    EntityManager::world3D->setNbIterationsPositionSolver(positionIterations3D);
}

void EntityManager::update()
{
    #ifdef Physics2D
        EntityManager::world.Step(1.0f/float(PhysicsTimeStep), velocityIterations, positionIterations);
    #endif

    #ifdef Physics3D
        EntityManager::world3D->update(1.0f/float(PhysicsTimeStep3D));
    #endif

    tree.clear();

    for (Entity *entity : EntityManager::entities)
    {
        entity->update();
        tree.insert(entity);
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
}

void EntityManager::setBounds(Rectangle bounds)
{
    EntityManager::tree.setBounds(bounds);
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
    std::vector<Entity*> renderCalls = EntityManager::tree.retrieve({EntityManager::camera.target.x - EntityManager::camera.offset.x, EntityManager::camera.target.y - EntityManager::camera.offset.y, (float)GetScreenWidth(), (float)GetScreenHeight()});
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
                if (EntityManager::isInCamera(entity)) entity->getComponent<Object>()->renderColliders();
            }
            else if (entity->hasComponent<Collider>())
            {
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