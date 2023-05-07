#include "headers/Component.h"
#include "headers/toolbox.h"

// ------------------------ Component ---------------------------------
Component::Component() { }
void Component::update(Entity* entity) { }
void Component::render() { }
void Component::dispose() { }
bool Component::operator==(const Component& other) const
{
    return this->id == other.id;
}

// -------------------------- OBJECT --------------------------
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
    entity->pos = this->pos;
    entity->scale = this->scale;
    entity->rotation = this->rotation;
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

// ----------------------------- BODY --------------------------------
Body::Body()
{
    top = {0, 0, 0, 0};
    down = {0, 0, 0, 0};
    left = {0, 0, 0, 0};
    right = {0, 0, 0, 0};
}
void Body::update(Entity* entity)
{
    this->top.x = this->rec.x + colliderThickness;
    this->top.y = this->rec.y - colliderThickness;
    this->top.width = this->rec.width - colliderThickness*2;
    this->top.height = colliderThickness;

    this->down.x = this->rec.x + colliderThickness;
    this->down.y = this->rec.y + this->rec.height;
    this->down.width = this->rec.width - colliderThickness*2;
    this->down.height = colliderThickness;

    this->left.x = this->rec.x - colliderThickness;
    this->left.y = this->rec.y + colliderThickness;
    this->left.width = colliderThickness;
    this->left.height = this->rec.height - colliderThickness*2;

    this->right.x = this->rec.x + this->rec.width;
    this->right.y = this->rec.y + colliderThickness;
    this->right.width = colliderThickness;
    this->right.height = this->rec.height - colliderThickness*2;
    Object::update(entity);
}
void Body::render()
{
    Object::render();
}
void Body::animate(Animation* animation)
{
    Object::animate(animation);
}
void Body::renderColliders()
{
    Object::renderColliders();
    DrawRectangleLinesEx(this->top, lineThickness, colliderColor);
    DrawRectangleLinesEx(this->down, lineThickness, colliderColor);
    DrawRectangleLinesEx(this->left, lineThickness, colliderColor);
    DrawRectangleLinesEx(this->right, lineThickness, colliderColor);
}
void Body::dispose() { }
bool Body::operator==(const Body& other) const
{
    return this->id == other.id;
}

// ------------------------ KINEMATIC BODY ----------------------
KinematicBody::KinematicBody()
{
    this->velocity = {0, 0};
    this->acceleration = {0, 0};
    this->bounce = false;
}
void KinematicBody::update(Entity* entity)
{
    this->velocity = addM(this->velocity, this->acceleration, GetFrameTime());
    this->pos = addM(this->pos, this->velocity, GetFrameTime());
    Body::update(entity);
}
void KinematicBody::render()
{
    Body::render();
}
void KinematicBody::animate(Animation* animation)
{
    Body::animate(animation);
}
void KinematicBody::renderColliders()
{
    Body::renderColliders();
}
void KinematicBody::pointTo(Vector2 point)
{
    this->rotation = (float) ((float) atan2(point.y - this->pos.y, point.x - this->pos.x) *  180 / PI);
}
bool KinematicBody::isGrounded()
{
    for (Entity* entity : EntityManager::entities)
    {
        if (entity->hasComponent<Body>())
        {
            if (entity->getComponent<Body>() != this)
            {
                if (CheckCollisionRecs(this->down, entity->getComponent<Body>()->rec))
                {
                    Vector2 delta = sub(this->pos, entity->getComponent<Body>()->pos);
                    float xDepth = (entity->getComponent<Body>()->scale.x + this->scale.x) - abs(delta.x);
                    float yDepth = (entity->getComponent<Body>()->scale.y + this->scale.y) - abs(delta.y);

                    if (xDepth > 0 && yDepth > 0)
                    {
                        if (xDepth > yDepth)
                        {
                            if (delta.y > 0)
                            {
                                return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void KinematicBody::dispose() { }
bool KinematicBody::operator==(const KinematicBody& other) const 
{
    return this->id == other.id;
}

// -------------------------- RIGID BODY --------------------------
RigidBody::RigidBody()
{
    this->velocity = {0, 0};
    this->acceleration = {0, 0};
    this->force = {0, 0};
    this->mass = 0;
    this->gravity = 0;
};
void RigidBody::update(Entity* entity)
{
    this->acceleration.y = this->gravity;
    this->velocity = addM(this->velocity, this->acceleration, GetFrameTime());
    this->pos = addM(this->pos, this->velocity, GetFrameTime());
    this->force = multiply(this->acceleration, this->mass);
    this->collisionCheck();
    Body::update(entity);
}
void RigidBody::collisionCheck()
{
    //between kinematics
    for (Entity* entity : EntityManager::entities)
    {
        //between kinematics
        if (entity->hasComponent<KinematicBody>())
        {
            if (CheckCollisionRecs(entity->getComponent<KinematicBody>()->rec, this->rec))
            {
                Vector2 delta = sub(this->pos, entity->getComponent<KinematicBody>()->pos);
                float xDepth = (entity->getComponent<KinematicBody>()->scale.x + this->scale.x) - abs(delta.x);
                float yDepth = (entity->getComponent<KinematicBody>()->scale.y + this->scale.y) - abs(delta.y);

                if (xDepth > 0 && yDepth > 0)
                {
                    if (xDepth < yDepth)
                    {
                        if (delta.x > 0)
                        {
                            entity->getComponent<KinematicBody>()->pos.x = this->pos.x - entity->getComponent<KinematicBody>()->scale.x;
                        }
                        else
                        {
                            entity->getComponent<KinematicBody>()->pos.x = this->pos.x + this->scale.x;
                        }
                        this->velocity.x = entity->getComponent<KinematicBody>()->velocity.x;
                        // kinematicBody.velocity.x = -kinematicBody.velocity.x;
                    }
                    else
                    {
                        if (delta.y > 0)
                        {
                            entity->getComponent<KinematicBody>()->pos.y = this->pos.y - entity->getComponent<KinematicBody>()->scale.y;
                        }
                        else
                        {
                            entity->getComponent<KinematicBody>()->pos.y = this->pos.y + this->scale.y;
                        }
                        // kinematicBody.velocity.y = -kinematicBody.velocity.y;
                    }
                }
            }
        }
        //between rigids
        if (entity->hasComponent<RigidBody>())
        {
            if (entity->getComponent<RigidBody>() != this)
            {
                if (CheckCollisionRecs(this->rec, entity->getComponent<RigidBody>()->rec) && entity->getComponent<RigidBody>())
                {
                    Vector2 delta = sub(this->pos, entity->getComponent<RigidBody>()->pos);
                    float xDepth = (entity->getComponent<RigidBody>()->scale.x + this->scale.x) - abs(delta.x);
                    float yDepth = (entity->getComponent<RigidBody>()->scale.y + this->scale.y) - abs(delta.y);

                    if (xDepth > 0 && yDepth > 0)
                    {
                        if (xDepth < yDepth)
                        {
                            if (delta.x > 0)
                            {
                                // right
                                entity->getComponent<RigidBody>()->pos.x = this->pos.x - entity->getComponent<RigidBody>()->scale.x;
                            }
                            else
                            {
                                // left
                                entity->getComponent<RigidBody>()->pos.x = this->pos.x + this->scale.x;
                            }
                            entity->getComponent<RigidBody>()->velocity.x = this->velocity.x;
                        }
                        else
                        {
                            if (delta.y > 0)
                            {
                                // top
                                entity->getComponent<RigidBody>()->pos.y = this->pos.y - entity->getComponent<RigidBody>()->scale.y;
                            }
                            else
                            {
                                // down
                                entity->getComponent<RigidBody>()->pos.y = this->pos.y + this->scale.y;
                                if (entity->getComponent<RigidBody>()->velocity.x != 0)
                                {
                                    if (entity->getComponent<RigidBody>()->velocity.x >= 0)
                                    {
                                        entity->getComponent<RigidBody>()->velocity.x -= 100 * entity->getComponent<RigidBody>()->mass * GetFrameTime();
                                    }
                                    else if (entity->getComponent<RigidBody>()->velocity.x <= 0)
                                    {
                                        entity->getComponent<RigidBody>()->velocity.x += 100 * entity->getComponent<RigidBody>()->mass * GetFrameTime();
                                    }
                                }
                            }
                            entity->getComponent<RigidBody>()->velocity.y = 0;
                        }
                    }
                }
            }
        }
    }
}
void RigidBody::render()
{
    Body::render();
}
void RigidBody::animate(Animation* animation)
{
    Body::animate(animation);
}
void RigidBody::renderColliders()
{
    Body::renderColliders();
}
void RigidBody::pointTo(Vector2 point)
{
    this->rotation = (float) ((float) atan2(point.y - this->pos.y, point.x - this->pos.x) *  180 / PI);
}
bool RigidBody::isGrounded()
{
    for (Entity* entity : EntityManager::entities)
    {
        if (entity->hasComponent<Body>())
        {
            if (entity->getComponent<Body>() != this)
            {
                if (CheckCollisionRecs(this->rec, entity->getComponent<Body>()->rec))
                {
                    Vector2 delta = sub(this->pos, entity->getComponent<Body>()->pos);
                    float xDepth = (entity->getComponent<Body>()->scale.x + this->scale.x) - abs(delta.x);
                    float yDepth = (entity->getComponent<Body>()->scale.y + this->scale.y) - abs(delta.y);

                    if (xDepth > 0 && yDepth > 0)
                    {
                        if (xDepth > yDepth)
                        {
                            if (delta.y > 0)
                            {
                                return false;
                            }
                            else
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void RigidBody::dispose() { }
bool RigidBody::operator==(const RigidBody& other) const 
{
    return this->id == other.id;
}

// -------------------------- STATIC BODY -------------------------
StaticBody::StaticBody()
{
    this->friction = 1000;
}
void StaticBody::update(Entity* entity)
{
    Body::update(entity);
    this->collisionCheck();
}
void StaticBody::collisionCheck()
{
    for (Entity* entity : EntityManager::entities)
    {
        //kinematics
        if (entity->hasComponent<KinematicBody>())
        {
            if (entity->getComponent<KinematicBody>()->isColliding(this))
            {
                Vector2 delta = sub(this->pos, entity->getComponent<KinematicBody>()->pos);
                float xDepth = (entity->getComponent<KinematicBody>()->scale.x + scale.x) - abs(delta.x);
                float yDepth = (entity->getComponent<KinematicBody>()->scale.y + scale.y) - abs(delta.y);

                if (xDepth > 0 && yDepth > 0)
                {
                    if (xDepth < yDepth && (CheckCollisionRecs(entity->getComponent<KinematicBody>()->right, this->rec) || CheckCollisionRecs(entity->getComponent<KinematicBody>()->left, this->rec)))
                    {
                        if (delta.x > 0)
                        {
                            if (this->checkLeft)
                            {
                                entity->getComponent<KinematicBody>()->pos.x = this->pos.x - entity->getComponent<KinematicBody>()->scale.x;
                                entity->getComponent<KinematicBody>()->rec.x = this->rec.x - entity->getComponent<KinematicBody>()->rec.width;
                            }
                        }
                        else
                        {
                            if (this->checkRight)
                            {
                                entity->getComponent<KinematicBody>()->pos.x = this->pos.x + this->scale.x;
                                entity->getComponent<KinematicBody>()->rec.x = this->rec.x + this->rec.width;
                            }
                        }
                        if (entity->getComponent<KinematicBody>()->bounce)
                            entity->getComponent<KinematicBody>()->velocity.x = -entity->getComponent<KinematicBody>()->velocity.x;
                    }
                    else
                    {
                        if (CheckCollisionRecs(entity->getComponent<KinematicBody>()->down, this->rec) || (CheckCollisionRecs(entity->getComponent<KinematicBody>()->top, this->rec)))
                        {
                            if (delta.y > 0)
                            {
                                if (this->checkDown)
                                {
                                    entity->getComponent<KinematicBody>()->pos.y = this->pos.y - entity->getComponent<KinematicBody>()->scale.y;
                                    entity->getComponent<KinematicBody>()->rec.y = this->rec.y - entity->getComponent<KinematicBody>()->rec.height;
                                }
                            }
                            else
                            {
                                if (this->checkUp)
                                {
                                    entity->getComponent<KinematicBody>()->pos.y = this->pos.y + this->scale.y;
                                    entity->getComponent<KinematicBody>()->rec.y = this->rec.y + this->rec.height;
                                }
                            }
                            if (entity->getComponent<KinematicBody>()->bounce)
                                entity->getComponent<KinematicBody>()->velocity.y = -entity->getComponent<KinematicBody>()->velocity.y;
                        }
                    }
                }
            }
        }

        //rigids
        if (entity->hasComponent<RigidBody>())
        {
            if (entity->getComponent<RigidBody>()->isColliding(this))
            {
                Vector2 delta = sub(this->pos, entity->getComponent<RigidBody>()->pos);
                float xDepth = (entity->getComponent<RigidBody>()->scale.x + this->scale.x) - abs(delta.x);
                float yDepth = (entity->getComponent<RigidBody>()->scale.y + this->scale.y) - abs(delta.y);

                if (xDepth > 0 && yDepth > 0)
                {
                    if (xDepth < yDepth && (CheckCollisionRecs(entity->getComponent<RigidBody>()->right, this->rec) || CheckCollisionRecs(entity->getComponent<RigidBody>()->left, this->rec)))
                    {
                        if (delta.x > 0)
                        {
                            if (this->checkLeft)
                            {
                                entity->getComponent<RigidBody>()->pos.x = this->pos.x - entity->getComponent<RigidBody>()->scale.x;
                                entity->getComponent<RigidBody>()->rec.x = this->rec.x - entity->getComponent<RigidBody>()->rec.width;
                            }
                        }
                        else
                        {
                            if (this->checkRight)
                            {
                                entity->getComponent<RigidBody>()->pos.x = this->pos.x + this->scale.x;
                                entity->getComponent<RigidBody>()->rec.x = this->rec.x + this->rec.width;
                            }
                        }
                        entity->getComponent<RigidBody>()->velocity.x = -entity->getComponent<RigidBody>()->velocity.x;
                    }
                    else
                    {
                        if (CheckCollisionRecs(entity->getComponent<RigidBody>()->down, this->rec) || (CheckCollisionRecs(entity->getComponent<RigidBody>()->top, this->rec)))
                        {
                            if (delta.y > 0)
                            {
                                if (this->checkDown)
                                {
                                    entity->getComponent<RigidBody>()->pos.y = this->pos.y - entity->getComponent<RigidBody>()->scale.y;
                                    entity->getComponent<RigidBody>()->rec.y = this->rec.y - entity->getComponent<RigidBody>()->rec.height;
                                    entity->getComponent<RigidBody>()->velocity.y = 0;
                                    if (entity->getComponent<RigidBody>()->velocity.x > 0.5f)
                                    {
                                        entity->getComponent<RigidBody>()->velocity.x -= this->friction * entity->getComponent<RigidBody>()->mass * GetFrameTime();
                                    }
                                    else if (entity->getComponent<RigidBody>()->velocity.x < -0.5f)
                                    {
                                        entity->getComponent<RigidBody>()->velocity.x += this->friction * entity->getComponent<RigidBody>()->mass * GetFrameTime();
                                    }
                                    else
                                    {
                                        entity->getComponent<RigidBody>()->velocity.x = 0;
                                    }
                                }
                            }
                            else
                            {
                                if (this->checkUp)
                                {
                                    entity->getComponent<RigidBody>()->pos.y = this->pos.y + this->scale.y;
                                    entity->getComponent<RigidBody>()->rec.y = this->rec.y + this->rec.height;
                                    entity->getComponent<RigidBody>()->velocity.y = -entity->getComponent<RigidBody>()->velocity.y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void StaticBody::render()
{
    Body::render();
}
void StaticBody::animate(Animation* animation)
{
    Body::animate(animation);
}
void StaticBody::renderColliders()
{
    Body::renderColliders();
}
void StaticBody::dispose() { }
bool StaticBody::operator==(const StaticBody& other) const 
{
    return this->id == other.id;
}

// ------------------ Sprite -------------------------
Sprite::Sprite()
{
    this->pos = {0, 0};
    this->scale = {0, 0};
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
    entity->pos = this->pos;
    entity->scale = this->scale;
    entity->rotation = this->rotation;
    Component::update(entity);
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

// --------------------------- BLOOM -----------------------------
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
    this->pos = center(entity->pos, entity->scale);
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

// ------------------------------- Physics body ------------------------

PhysicsBody::PhysicsBody()
{
    this->type = b2_dynamicBody;
    this->density = 1.0f;
    this->friction = 0.3f;
}
void PhysicsBody::init()
{
    this->bodyDef.type = this->type;
    this->body = EntityManager::world.CreateBody(&this->bodyDef);
    this->box.SetAsBox(this->scale.x*0.5f, this->scale.y*0.5f);
    this->fixtureDef.shape = &box;
    this->fixtureDef.density = this->density;
    this->fixtureDef.friction = this->friction;
    this->body->CreateFixture(&this->fixtureDef);
    this->body->SetTransform(Vector2ToB2Vec2(this->pos), this->rotation*DEG2RAD);
    this->originX = this->scale.x*0.5f;
    this->originY = this->scale.y*0.5f;
}
void PhysicsBody::update(Entity* entity)
{
    Object::update(entity);
    this->pos = B2Vec2ToVector2(this->body->GetPosition());
    this->rotation = this->body->GetAngle()*RAD2DEG;
    entity->pos = this->pos;
    entity->scale = this->scale;
}
void PhysicsBody::render()
{
    Object::render();
}
void PhysicsBody::dispose()
{
    Object::dispose();
}
bool PhysicsBody::operator==(const PhysicsBody& other) const
{
    return this->id == other.id;
}