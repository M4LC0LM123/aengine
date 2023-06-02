#include "headers/KinematicBody.h"

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
    std::vector<Entity*> potentialCollision = EntityManager::quadtree.retrieve({this->pos.x - 50, this->pos.y - 50, this->scale.x + 100, this->scale.y + 100});

    for (Entity* entity : potentialCollision)
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