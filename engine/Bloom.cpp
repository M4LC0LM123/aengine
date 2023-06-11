#include "headers/Bloom.h"

Bloom::Bloom()
{
    this->intensity = BLOOM_INTENSITY;
    this->color = WHITE;
    this->isActive = true;
    this->colors = nullptr;
    this->colorIndex = 0;
    this->pos = {0, 0};
    this->originX = 0;
    this->originY = 0;
}
void Bloom::update(Entity* entity)
{
    this->pos = center({entity->pos.x, entity->pos.y}, {entity->scale.x, entity->scale.y});
    if (entity->hasComponent<Object>()) this->originX = entity->getComponent<Object>()->originX;
    if (entity->hasComponent<Object>()) this->originY = entity->getComponent<Object>()->originY;
    if (this->intensity < 0) this->intensity = entity->scale.x;
}
void Bloom::render()
{
    Component::render();
    if (this->intensity != 0) DrawCircleGradient(this->pos.x - this->originX, this->pos.y - this->originY, this->intensity, this->color, BLANK);
}
void Bloom::setColor(Color color)
{
    this->color = color;
}
void Bloom::setColorFromShape(Entity* entity)
{
    if (entity->hasComponent<Object>())
    {
        this->color = entity->getComponent<Object>()->color;
    }
}
void Bloom::setColorFromImage(Entity* entity)
{
    if (entity->hasComponent<Sprite>())
    {
        this->colors = LoadImageColors(LoadImageFromTexture(entity->getComponent<Sprite>()->texture));
        this->color = this->colors[int(entity->getComponent<Object>()->frame * entity->getComponent<Object>()->frameScale.x)];
    }
    else if (entity->hasComponent<Object>())
    {
        this->colors = LoadImageColors(LoadImageFromTexture(entity->getComponent<Object>()->texture));
        this->color = this->colors[int(entity->getComponent<Object>()->frame * entity->getComponent<Object>()->frameScale.x)];
    }
    
}
void Bloom::dispose()
{
    Component::dispose();
    UnloadImageColors(this->colors);
}
bool Bloom::operator==(const Bloom& other) const
{
    return this->id == other.id;
}