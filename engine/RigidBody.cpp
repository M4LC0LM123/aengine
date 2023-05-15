#include "headers/RigidBody.h"

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