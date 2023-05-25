#pragma once
#include "iostream"
#include "raylib.h"

struct AmbientAudio : Component
{
    private:
        Sound m_sound;
        bool m_paused;
        Vector2 m_pos;

    public: 
        Vector2 target;

        AmbientAudio();
        virtual void update(Entity* entity) override;
        virtual void set(std::string path);
        virtual void set(Sound sound);
        virtual Sound get();
        virtual void paused(bool p);
        virtual void play();
        virtual void dispose() override;
};
