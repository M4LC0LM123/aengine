#include "headers/StaticBody.h"

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