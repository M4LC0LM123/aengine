#pragma once

struct BoxCollider : public Collider
{
    private:
        Rectangle m_collider;

    float width;
    float height;

    BoxCollider();

    virtual void renderColliders() override;
    virtual void update(Entity* entity) override;
    virtual void set(float x, float y, float width, float height);
    virtual bool overlaps(BoxCollider* other);

};
