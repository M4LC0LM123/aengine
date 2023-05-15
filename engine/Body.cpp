#include "headers/Body.h"

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