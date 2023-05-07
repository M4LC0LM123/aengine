#pragma once
#include "vector"

class EntityManager
{
    public:
        static std::vector<Entity*> entities;
        static Camera2D camera;
        static bool useCamera;
        static bool renderCollidersBool;
        static bool debugBool;
        static b2Vec2 gravity;
        static b2World world;

        static void update();
        static void setCamera(Camera2D* camera);
        static bool isInCamera(Entity* other);
        static void render();
        static void renderColliders(bool debugMode);
        static void dispose();
        static void kill(Entity* entity);
        static void sortEntities();
        template<typename T>
        static void instantiate(T* entity, Vector2 pos, Vector2 scale, float rotation);
};
