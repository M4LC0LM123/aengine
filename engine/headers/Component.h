#pragma once

class Component
{
    public:
        Component();
        virtual void update(Entity* entity);
        virtual void render();
        virtual void dispose();
        bool operator==(const Component& other) const;

    private:
        int id;
};

class Object : public Component
{
    public:
        Vector2 pos;
        Vector2 scale;
        Vector2 textureScale;
        Vector2 texturePos;
        float rotation; 
        Rectangle rec;
        Color color = WHITE;
        Color tint = WHITE;
        Texture2D texture;
        float frame = 0;
        Vector2 frameScale = (Vector2){0, 0};
        float originX = 0;
        float originY = 0;
        bool flipH;
        bool flipV;
        bool isAnimActive;

        Object();
        virtual void setFrame(Vector2 frameScale, float frame);
        virtual bool isColliding(Object* other);
        virtual void update(Entity* entity) override;
        virtual void animate(Animation* animation);
        virtual void render() override;
        virtual void renderColliders();
        virtual void setTexturePos(Vector2 pos);
        virtual void setTexturePos(float x, float y);
        virtual void textureOnRec();
        virtual void dispose() override;
        bool operator==(const Object& other) const;

    private:
        int id;

        bool m_textureOnPos;
};

class Body : public Object
{
    public:
        Rectangle top;
        Rectangle down;
        Rectangle left;
        Rectangle right;

        Body();
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void animate(Animation* animation) override;
        virtual void renderColliders() override;
        virtual void dispose() override;
        bool operator==(const Body& other) const;

    private:
        int id;

};

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

class StaticBody : public Body
{
    public:
        float friction;
        bool checkUp = true;
        bool checkDown = true;
        bool checkLeft = true;
        bool checkRight = true;

        StaticBody();
        virtual void update(Entity* entity) override;
        virtual void collisionCheck();
        virtual void render() override;
        virtual void animate(Animation* animation) override;
        virtual void renderColliders() override;
        virtual void dispose() override;
        bool operator==(const StaticBody& other) const;

    private:
        int id;
};

class Sprite : public Component
{
    public:
        Vector2 pos;
        Vector2 scale;
        float rotation; 
        Color color = WHITE;
        Color tint = WHITE;
        Texture2D texture;
        float frame = 0;
        Vector2 frameScale = (Vector2){0, 0};
        float originX = 0;
        float originY = 0;
        bool flipH;
        bool flipV;
        bool isAnimActive;

        Sprite();
        virtual void setFrame(Vector2 frameScale, float frame);
        virtual void update(Entity* entity) override;
        virtual void animate(Animation* animation);
        virtual void render() override;
        virtual void dispose() override;
        bool operator==(const Sprite& other) const;

    private:
        int id;
};

class Bloom : public Component
{
    public:
        float intensity; // bloom radius
        Color color;
        bool isActive;

        Bloom();
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void dispose() override;
        virtual void setColor(Color color);
        virtual void setColorFromShape(Entity* entity);
        virtual void setColorFromImage(Entity* entity);
        bool operator==(const Bloom& other) const;

    private:
        int id;
        Color* colors;
        int colorIndex;
        Vector2 pos;
        int originX;
        int originY;
};

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