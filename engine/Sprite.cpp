#include "headers/Sprite.h"

Sprite::Sprite(Entity* entity)
{
    this->pos = {entity->pos.x, entity->pos.y};
    this->scale = {entity->scale.x, entity->scale.y};
    this->rotation = 0;
    this->color = WHITE;
    this->tint = WHITE;
    this->frame = 0;
    this->frameScale = {0, 0};
    this->originX = 0;
    this->originY = 0;
    this->flipH = false;
    this->flipV = false;
    this->isAnimActive = false;
}

void Sprite::setFrame(Vector2 frameScale, float frame)
{
    this->frame = frame;
    this->frameScale = frameScale;
}
void Sprite::update(Entity* entity)
{
    Component::update(entity);
    this->pos = {entity->pos.x, entity->pos.y};
    this->scale = {entity->scale.x, entity->scale.y};
    this->rotation = entity->rotation.z;
}
void Sprite::animate(Animation* animation)
{
    animation->frameCounter++;
    if (animation->frameCounter >= (GetFPS() / animation->speed))
    {
        animation->frameCounter = 0;
        animation->frame++;
        if (animation->frame > animation->frames)
            animation->frame = 0;
    }
    if (!flipH && !flipV)
        DrawTexturePro(animation->texture, (Rectangle){animation->frame * animation->frameSize.x, 0, animation->frameSize.x, animation->frameSize.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    else if (flipH && !flipV)
        DrawTexturePro(animation->texture, (Rectangle){(animation->frame * animation->frameSize.x) + animation->frameSize.x, 0, -animation->frameSize.x, animation->frameSize.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    else if (!flipH && flipV)
        DrawTexturePro(animation->texture, (Rectangle){animation->frame * animation->frameSize.x, animation->frameSize.y, animation->frameSize.x, -animation->frameSize.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    else if (flipH && flipV)
        DrawTexturePro(animation->texture, (Rectangle){(animation->frame * animation->frameSize.x) + animation->frameSize.x, animation->frameSize.y, -animation->frameSize.x, -animation->frameSize.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    this->isAnimActive = true;
}
void Sprite::render()
{
    DrawRectangleRec((Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, this->color);

    if (!this->isAnimActive)
    {
        if (!flipH && !flipV)
            DrawTexturePro(this->texture, (Rectangle){this->frame * this->frameScale.x, 0, this->frameScale.x, this->frameScale.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
        else if (flipH && !flipV)
            DrawTexturePro(this->texture, (Rectangle){(this->frame * this->frameScale.x) + this->frameScale.x, 0, -this->frameScale.x, this->frameScale.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
        if (!flipH && flipV)
            DrawTexturePro(this->texture, (Rectangle){this->frame * this->frameScale.x, this->frameScale.y, this->frameScale.x, -this->frameScale.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
        else if (flipH && flipV)
            DrawTexturePro(this->texture, (Rectangle){(this->frame * this->frameScale.x) + this->frameScale.x, this->frameScale.y, -this->frameScale.x, -this->frameScale.y}, (Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    }
    Component::render();
}
void Sprite::dispose() 
{ 
    UnloadTexture(this->texture);
    Component::dispose();
}
bool Sprite::operator==(const Sprite& other) const
{
    return this->id == other.id;
}