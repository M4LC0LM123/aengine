#include "headers/CircleCollider.h"
#include "headers/BoxCollider.h"

CircleCollider::CircleCollider()
{
    this->radius = 0;
}

void CircleCollider::renderColliders()
{
    Collider::renderColliders();
    DrawCircleLines(this->x, this->y, this->radius, colliderColor);
}

void CircleCollider::update(Entity* entity)
{
    Collider::update(entity);
}

void CircleCollider::set(float x, float y, float radius)
{
    Collider::set(x, y);
    this->x = x;
    this->y = y;
    this->radius = radius;
}

bool CircleCollider::overlaps(CircleCollider* other)
{
    Collider::overlaps(other);
    if (CheckCollisionCircles(Vector2{this->x, this->y}, this->radius, Vector2{other->x, other->y}, other->radius))
    {   
        return true;
    }
    else
    {
        return false;
    }
}

bool CircleCollider::overlaps(BoxCollider* other)
{
    Collider::overlaps(other);
    Rectangle rec = {other->x, other->y, other->width, other->height};
    if (CheckCollisionCircleRec(Vector2{this->x, this->y}, this->radius, rec))
    {   
        return true;
    }
    else
    {
        return false;
    }
}

