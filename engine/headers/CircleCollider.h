#pragma once
#include "BoxCollider.h"

struct BoxCollider;

struct CircleCollider : public Collider
{
    float radius;

    CircleCollider();
    virtual ~CircleCollider() = default;
    virtual void renderColliders() override;
    virtual void update(Entity* entity) override;
    virtual void set(float x, float y, float radius);
    virtual bool overlaps(CircleCollider* other);
    virtual bool overlaps(BoxCollider* other);
        
};
