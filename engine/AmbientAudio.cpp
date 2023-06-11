#include "headers/AmbientAudio.h"
#include "iostream"

AmbientAudio::AmbientAudio()
{
    this->m_pos = {0, 0};
    this->m_paused = false;
    this->target = {0, 0};
    this->audioType = SOUND;
}

void AmbientAudio::update(Entity* entity)
{
    Component::update(entity);
    this->m_pos = {entity->pos.x, entity->pos.y};

    if (EntityManager::isInCamera(entity) && !this->m_paused)
    {
        if (this->audioType == SOUND)
            ResumeSound(this->m_sound);
        else if (this->audioType == MUSIC)
            ResumeMusicStream(this->m_music);
    }
    else
    {
        if (this->audioType == SOUND)
            PauseSound(this->m_sound);
        else if (this->audioType == MUSIC)
            PauseMusicStream(this->m_music);
    }

    //std::cout << std::to_string(getDistance(this->target, this->m_pos)) << "\n";
    // std::cout << std::to_string(this->m_pos.x) << ", " << std::to_string(this->m_pos.y) << "\n";
    if (getDistance(this->target, this->m_pos) <= 1000)
    {
        if (this->audioType == SOUND)
            SetSoundVolume(this->m_sound, 1.0f - getDistance(this->target, this->m_pos) / 1000.0f);
        else if (this->audioType == MUSIC)
            SetMusicVolume(this->m_music, 1.0f - getDistance(this->target, this->m_pos) / 1000.0f);
    }
}

void AmbientAudio::set(std::string path)
{
    if (this->audioType == SOUND)
        this->m_sound = LoadSound(path.c_str());
    else if (this->audioType == MUSIC)
        this->m_music = LoadMusicStream(path.c_str());
}

void AmbientAudio::set(Sound sound)
{
    this->m_sound = sound;
}

void AmbientAudio::set(Music music)
{
    this->m_music = music;
}

void AmbientAudio::set(AudioType at)
{
    this->audioType = at;
}

Sound AmbientAudio::getSound()
{
    return this->m_sound;
}

Music AmbientAudio::getMusicStream()
{
    return this->m_music;
}

void AmbientAudio::paused(bool p)
{
    this->m_paused = p;
}  

void AmbientAudio::play()
{
    if (this->audioType == SOUND)
        PlaySound(this->m_sound);
    else if (this->audioType == MUSIC)
        PlayMusicStream(this->m_music);
}

void AmbientAudio::dispose()
{
    Component::dispose();
    if (this->audioType == SOUND)
        UnloadSound(this->m_sound);
    else if (this->audioType == MUSIC)
        UnloadMusicStream(this->m_music);
}