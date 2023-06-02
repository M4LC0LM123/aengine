#pragma once

class Bloom : public Component
{
    public:
        float intensity; // bloom radius
        Color color;
        bool isActive;

        Bloom();
        virtual ~Bloom() = default;
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