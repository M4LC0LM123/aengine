#pragma once

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