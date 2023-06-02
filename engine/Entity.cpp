#include "headers/Entity.h"
#include "headers/EntityManager.h"
#include "headers/Bloom.h"
#include "headers/Object.h"

// ------------------------ Entity ---------------------------------
Entity::Entity()
{
    this->pos = {0, 0};
    this->scale = {0, 0};
    this->rotation = 0;
    EntityManager::entities.push_back(this);
    if (EntityManager::entities.size() == 0) this->tag = "Entity";
    else this->tag = "Entity" + std::to_string(EntityManager::entities.size());
    EntityManager::sortEntities();
}
Entity::~Entity() { }
void Entity::update() 
{
    for (Component* component : this->components)
    {
        component->update(this);
    }
}
template<typename T, typename... Args>
T* Entity::addComponent(Args &&...args)
{
    T* component = new T(std::forward<Args>(args)...);
    components.push_back(component);
    if (this->hasComponent<Object>())
    {
        this->getComponent<Object>()->pos = this->pos;
        this->getComponent<Object>()->scale = this->scale;
        this->getComponent<Object>()->rotation = this->rotation;
    }
    return component;
}
template<typename T>
void Entity::addComponent(T* component)
{
    components.push_back(component);
    if (this->hasComponent<Object>())
    {
        this->getComponent<Object>()->pos = this->pos;
        this->getComponent<Object>()->scale = this->scale;
        this->getComponent<Object>()->rotation = this->rotation;
    }
}
template<typename T>
T* Entity::getComponent()
{
    for (Component *component : components)
    {
        T* derived = dynamic_cast<T*>(component);
        if (derived)
        {
            return derived;
        }
    }
    return nullptr;
}
template<typename T>
bool Entity::hasComponent()
{
    for (Component *component : components)
    {
        if (dynamic_cast<T*>(component))
        {
            return true;
        }
    }
    return false;
}
void Entity::render() 
{ 
    for (Component* component : this->components)
    {
        component->render();
    }
}
void Entity::resetBloom()
{
    if (this->hasComponent<Bloom>())
    {
        this->getComponent<Bloom>()->intensity = BLOOM_INTENSITY;
    }
}
Rectangle Entity::getBoundingBox()
{
    return Rectangle {this->pos.x, this->pos.y, this->scale.x, this->scale.y};
}
void Entity::dispose() 
{
    for (Component* component : this->components)
    {
        component->dispose();
    }
    components.clear();
}
bool Entity::operator==(const Entity& other) const
{
    return this->id == other.id;
}
void Entity::setZ(int z)
{
    this->zIndex = z;
}
int Entity::getZ()
{
    return this->zIndex;
}

// ------------------------ PARTICLE -----------------------------
Particle::Particle(ParticleData particleData)
{
    this->acceleration = {0, 5};
    this->velocity = {(float)GetRandomValue(-100, 100), (float)GetRandomValue(200, 0)};
    switch (particleData.pst)
    {
        case RECTANGULAR:
            this->pos.x = (float)GetRandomValue((int) (particleData.x - 20), (int) (particleData.x + 20));
            this->pos.y = (float)GetRandomValue((int)(particleData.y - 20), (int)(particleData.y + 20));
            break;
        case POINT:
            this->pos.x = (float)GetRandomValue((int) (particleData.x), (int) (particleData.x));
            this->pos.y = (float)GetRandomValue((int)(particleData.y), (int)(particleData.y));
            break;
        
        default:
            this->pos.x = (float)GetRandomValue((int) (particleData.x - 20), (int) (particleData.x + 20));
            this->pos.y = (float)GetRandomValue((int)(particleData.y - 20), (int)(particleData.y + 20));
            break;
    }
    if (particleData.pb == TOPDOWN)
    {
        this->velocity = multiplyV2(this->velocity, randBitVector2());
    }
    this->pb = particleData.pb;
    this->lifeSpan = particleData.lifeSpan;
    this->radius = particleData.radius;
    this->color = particleData.color;
}
void Particle::update()
{
    Entity::update();
    switch (this->pb)
    {
        case KINEMATIC:
            this->velocity = addM(this->velocity, this->acceleration, GetFrameTime());
            break;
        
        default:
            this->velocity = addM(this->velocity, this->acceleration, GetFrameTime());
            break;
    }

    this->pos = addM(this->pos, this->velocity, GetFrameTime());
    this->lifeSpan -= 100 * GetFrameTime();
}
void Particle::render()
{
    DrawCircleV(this->pos, this->radius, this->color);
    Entity::render();
}
bool Particle::isDead()
{
    if (this->lifeSpan <= 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
void Particle::dispose() { }
bool Particle::operator==(const Particle& other) const
{
    return this->id == other.id;
}
