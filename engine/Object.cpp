#include "raylib.h"
#include "headers/Object.h"

Object::Object()
{
    this->pos = {0, 0};
    this->scale = {0, 0};
    this->textureScale = {0, 0};
    this->texturePos = {0, 0};
    this->rotation = 0;
    this->rec = {0, 0, 0, 0};
    this->color = WHITE;
    this->tint = WHITE;
    this->frame = 0;
    this->frameScale = {0, 0};
    this->originX = 0;
    this->originY = 0;
    this->flipH = false;
    this->flipV = false;
    this->isAnimActive = false;
    this->m_textureOnPos = true;
}

void Object::setFrame(Vector2 frameScale, float frame)
{
    this->frame = frame;
    this->frameScale = frameScale;
}

bool Object::isColliding(Object* other)
{
    return this->pos.x < other->pos.x + other->scale.x && 
    this->pos.x + this->scale.x > other->pos.x && 
    this->pos.y < other->pos.y + other->scale.y && 
    this->pos.y + this->scale.y > other->pos.y;
}

void Object::update(Entity* entity)
{
    Component::update(entity);
    entity->pos = {this->pos.x, this->pos.y, entity->pos.z};
    entity->scale = {this->scale.x, this->scale.y, entity->scale.z};
    entity->rotation = {0, 0, this->rotation};
    this->rec = {this->pos.x - this->originX, this->pos.y - this->originY, this->scale.x, this->scale.y};
    if (this->textureScale.x == 0) this->textureScale.x = this->scale.x;
    if (this->textureScale.y == 0) this->textureScale.y = this->scale.y;
    if (this->m_textureOnPos == true) this->texturePos = this->pos;
}

void Object::animate(Animation* animation)
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
        DrawTexturePro(animation->texture, (Rectangle){animation->frame * animation->frameSize.x, 0, animation->frameSize.x, animation->frameSize.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    else if (flipH && !flipV)
        DrawTexturePro(animation->texture, (Rectangle){(animation->frame * animation->frameSize.x) + animation->frameSize.x, 0, -animation->frameSize.x, animation->frameSize.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    else if (!flipH && flipV)
        DrawTexturePro(animation->texture, (Rectangle){animation->frame * animation->frameSize.x, animation->frameSize.y, animation->frameSize.x, -animation->frameSize.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    else if (flipH && flipV)
        DrawTexturePro(animation->texture, (Rectangle){(animation->frame * animation->frameSize.x) + animation->frameSize.x, animation->frameSize.y, -animation->frameSize.x, -animation->frameSize.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    this->isAnimActive = true;
}

void Object::render()
{
    DrawRectanglePro((Rectangle){this->pos.x, this->pos.y, this->scale.x, this->scale.y}, {originX, originY}, this->rotation, this->color);

    if (!this->isAnimActive)
    {
        if (!flipH && !flipV)
            DrawTexturePro(this->texture, (Rectangle){this->frame * this->frameScale.x, 0, this->frameScale.x, this->frameScale.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
        else if (flipH && !flipV)
            DrawTexturePro(this->texture, (Rectangle){(this->frame * this->frameScale.x) + this->frameScale.x, 0, -this->frameScale.x, this->frameScale.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
        if (!flipH && flipV)
            DrawTexturePro(this->texture, (Rectangle){this->frame * this->frameScale.x, this->frameScale.y, this->frameScale.x, -this->frameScale.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
        else if (flipH && flipV)
            DrawTexturePro(this->texture, (Rectangle){(this->frame * this->frameScale.x) + this->frameScale.x, this->frameScale.y, -this->frameScale.x, -this->frameScale.y}, (Rectangle){this->texturePos.x, this->texturePos.y, this->textureScale.x, this->textureScale.y}, (Vector2){this->originX, this->originY}, this->rotation, this->tint);
    }
    Component::render();
}

void Object::renderColliders()
{
    DrawRectangleLinesEx(this->rec, lineThickness, colliderColor);
}

void Object::setTexturePos(Vector2 pos)
{
    this->m_textureOnPos = false;
    this->texturePos = pos;
}

void Object::setTexturePos(float x, float y)
{
    this->m_textureOnPos = false;
    this->texturePos = {x, y};
}

void Object::textureOnRec()
{
    this->m_textureOnPos = true;
}

void Object::dispose() 
{ 
    UnloadTexture(this->texture);
    Component::dispose();
}

bool Object::operator==(const Object& other) const
{
    return this->id == other.id;
}
