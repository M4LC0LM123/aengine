#pragma once

class PhysicsBody : public Object
{
    public:
        float density;
        float friction;
        b2BodyType type;
        b2BodyDef bodyDef;
        b2Body* body;
        b2PolygonShape box;
        b2FixtureDef fixtureDef;

        PhysicsBody();
        virtual void init();
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void dispose() override;
        bool operator==(const PhysicsBody& other) const;
    
    private:
        int id;
};