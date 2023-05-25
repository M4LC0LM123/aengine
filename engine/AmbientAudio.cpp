#include "headers/AmbientAudio.h"
#include "iostream"

AmbientAudio::AmbientAudio()
{
    this->m_pos = {0, 0};
    this->m_paused = false;
    this->target = {0, 0};
}

void AmbientAudio::update(Entity* entity)
{
    Component::update(entity);
    this->m_pos = entity->pos;

    if (EntityManager::isInCamera(entity) && !this->m_paused)
    {
        ResumeSound(this->m_sound);
    }
    else
    {
        PauseSound(this->m_sound);
    }

    std::cout << std::to_string(getDistance(this->target, this->m_pos)) << "\n";
    // std::cout << std::to_string(this->m_pos.x) << ", " << std::to_string(this->m_pos.y) << "\n";
    if (getDistance(this->target, this->m_pos) <= 1000)
    {
        SetSoundVolume(this->m_sound, 1.0f - getDistance(this->target, this->m_pos) / 1000.0f);
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