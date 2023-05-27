#pragma once
#include "iostream"
#include "raylib.h"

struct AmbientAudio : Component
{
    private:
        Sound m_sound;
        Music m_music;
        bool m_paused;
        Vector2 m_pos;

    public: 
        Vector2 target;
        AudioType audioType;

        AmbientAudio();
        virtual void update(Entity* entity) override;
        virtual void set(std::string path);
        virtual void set(Sound sound);
        virtual void set(Music music);
        virtual void set(AudioType at);
        virtual Sound getSound();
        virtual Music getMusicStream();
        virtual void paused(bool p);
        virtual void play();
        virtual void dispose() override;
};
