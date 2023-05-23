#include "headers/BoxCollider.h"
#include "headers/CircleCollider.h"

BoxCollider::BoxCollider()
{
    this->width = 0;
    this->height = 0;
    this->m_collider = {0, 0, 0, 0};
}

void BoxCollider::renderColliders()
{
    Collider::renderColliders();
    DrawRectangleLinesEx(this->m_collider, lineThickness, colliderColor);
}

void BoxCollider::update(Entity *entity)
{
    Collider::update(entity);
    this->m_collider = {this->x, this->y, this->width, this->height};
}

void BoxCollider::set(float x, float y, float width, float height)
{
    Collider::set(x, y);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool BoxCollider::overlaps(BoxCollider *other)
{
    Collider::overlaps(other);
    Rectangle rec = {other->x, other->y, other->width, other->height};
    if (CheckCollisionRecs(this->m_collider, rec))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BoxCollider::overlaps(CircleCollider* other)
{
    Collider::overlaps(other);
    if (CheckCollisionCircleRec(Vector2{other->x, other->y}, other->radius, this->m_collider))
    {   
        return true;
    }
    else
    {
        return false;
    }
}
