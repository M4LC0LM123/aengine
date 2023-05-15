#include "headers/BoxCollider.h"

BoxCollider::BoxCollider()
{
    this->width = 0;
    this->height = 0;
    this->m_collider = {0, 0, 0, 0};
}

void BoxCollider::renderColliders()
{
    Collider::renderColliders();
    DrawRectangleRec(this->m_collider, colliderColor);
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
