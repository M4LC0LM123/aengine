#pragma once 

class KinematicBody : public Body
{
    public:
        Vector2 velocity;
        Vector2 acceleration;
        bool bounce = false;

        KinematicBody();
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void animate(Animation* animation) override;
        virtual void renderColliders() override;
        virtual void pointTo(Vector2 point);
        virtual bool isGrounded();
        virtual void dispose() override;
        bool operator==(const KinematicBody& other) const;

    private:
        int id;
};
