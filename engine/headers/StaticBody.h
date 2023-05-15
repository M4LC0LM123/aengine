#pragma once

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
