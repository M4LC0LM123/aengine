#include "headers/Collider.h"

Collider::Collider()
{
    this->x = 0;
    this->y = 0;
}

void Collider::update(Entity *entity) { Component::update(entity); }
void Collider::renderColliders() { }
void Collider::set(float x, float y) { }
bool Collider::overlaps(Collider *other) { }
