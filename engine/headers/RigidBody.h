#pragma once 

class RigidBody : public Body
{
    public:
        Vector2 velocity;
        Vector2 acceleration;
        Vector2 force;
        float mass;
        float gravity;

        RigidBody();
        virtual void collisionCheck();
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void animate(Animation* animation) override;
        virtual void renderColliders() override;
        virtual void pointTo(Vector2 point);
        virtual bool isGrounded();
        virtual void dispose() override;
        bool operator==(const RigidBody& other) const;

    private:
        int id;
};
