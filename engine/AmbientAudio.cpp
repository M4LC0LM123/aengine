#include "headers/AmbientAudio.h"
#include "iostream"

AmbientAudio::AmbientAudio()
{
    this->m_sound = {0, 0};
    this->m_paused = true;
}

void AmbientAudio::update(Entity* entity)
{
    Component::update(entity);

    if (!this->m_paused)
    {
        ResumeSound(this->m_sound);
    }
    else
    {
        PauseSound(this->m_sound);
    }

}

void AmbientAudio::set(std::string path)
{
    this->m_sound = LoadSound(path.c_str());
}

void AmbientAudio::set(Sound sound)
{
    this->m_sound = sound;
}

Sound AmbientAudio::get()
{
    return this->m_sound;
}

void AmbientAudio::paused(bool p)
{
    this->m_paused = p;
}  

void AmbientAudio::play()
{
    PlaySound(this->m_sound);
}

void AmbientAudio::dispose()
{
    Component::dispose();
    UnloadSound(this->m_sound);
}