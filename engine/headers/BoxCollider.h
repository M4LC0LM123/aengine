#pragma once
#include "CircleCollider.h"

struct CircleCollider;

struct BoxCollider : public Collider
{
    private:
        Rectangle m_collider;

    public:
        float width;
        float height;

    BoxCollider();

    virtual void renderColliders() override;
    virtual void update(Entity* entity) override;
    virtual void set(float x, float y, float width, float height);
    virtual bool overlaps(BoxCollider* other);
    virtual bool overlaps(CircleCollider* other);

};
