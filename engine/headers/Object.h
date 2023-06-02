#pragma once

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
        virtual ~Object() = default;
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