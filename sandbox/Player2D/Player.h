#pragma once

class Player : public Entity
{
    public:
        Animation anim;
        Vector2 velocity;
        bool debugInfo;
        Console console;
        Sound jumpSound;
        KinematicBody* kb;

        Player();
        void init();
        virtual void update() override;
        virtual void render() override;
        virtual void dispose() override;
        bool operator==(const Player& other) const;

    private:
        int id;
        int debugToggle;
};

