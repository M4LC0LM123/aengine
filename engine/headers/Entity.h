#ifndef ENTITY_H
#define ENTITY_H
#pragma once
#include "vector"
#include "toolbox.h"
#include "Animation.h"
#include "Component.h"

#define colliderThickness 5
#define colliderFraction 3
#define lineThickness 1

class Entity
{
    public:
        std::string tag;
        Vector2 pos;
        Vector2 scale;
        float rotation;
        std::vector<Component*> components;

        Entity();
        virtual ~Entity();
        virtual void update();
        template<typename T, typename... Args>
        T* addComponent(Args&&... args);
        template<typename T>
        void addComponent(T* component);
        template<typename T>
        T* getComponent();
        template<typename T>
        bool hasComponent();
        virtual void render();
        virtual void dispose();
        virtual void resetBloom();
        virtual std::vector<Entity*> getBoundingEntities();
        virtual std::vector<Entity*> getBoundingEntities(Rectangle area);
        virtual std::vector<Entity*> getBoundingEntities(float offset);
        virtual Rectangle getBoundingBox();
        bool operator==(const Entity& other) const;
        void setZ(int z);
        int getZ();

    private:
        int id;
        int zIndex = 0;
};

struct ParticleData
{
    float x;
    float y;
    Color color;
    float lifeSpan;
    float radius;
    ParticleBehaviour pb;
    ParticleSpawnType pst;
};

class Particle : public Entity
{
    private:
        ParticleBehaviour pb;

    public:
        Vector2 velocity;
        Vector2 acceleration;
        float lifeSpan;
        float radius;
        Color color;

        Particle(ParticleData particleData);
        virtual void update() override;
        virtual void render() override;
        bool isDead();
        virtual void dispose() override;
        bool operator==(const Particle& other) const;

    private:
        int id;
};

#endif