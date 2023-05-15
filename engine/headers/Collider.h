#pragma once 

struct Collider : public Component
{

    float x;
    float y;

    Collider();
    virtual void update(Entity* entity) override;
    virtual void renderColliders();
    virtual void set(float x, float y);
    virtual bool overlaps(Collider* other);

};
