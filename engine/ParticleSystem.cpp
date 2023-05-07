#include "headers/ParticleSystem.h"

ParticleSystem::ParticleSystem(ParticleData particleData)
{
    this->particleData = particleData;
    EntityManager::entities.push_back(this);
}

void ParticleSystem::addParticle()
{
    Particle* particle = new Particle(this->particleData);
    this->particles.push_back(particle);
}

void ParticleSystem::addSpecificParticle(ParticleData particleData)
{
    Particle* particle = new Particle(particleData);
    this->particles.push_back(particle);
}

void ParticleSystem::removeParticles()
{
    for (Particle *particle : this->deletedParticles)
    {
        for (auto it = EntityManager::entities.begin(); it != EntityManager::entities.end(); ++it)
        {
            if (*it == particle)
            {
                EntityManager::entities.erase(it);
                break;
            }
        }
        for (auto it = this->particles.begin(); it != this->particles.end(); ++it)
        {
            if (*it == particle)
            {
                this->particles.erase(it);
                break;
            }
        }
    }
}

void ParticleSystem::setParticleData(ParticleData particleData)
{
    this->particleData = particleData;
    EntityManager::entities.push_back(this);
}

void ParticleSystem::update() 
{
    for (Particle* particle : particles)
    {
        if (particle->isDead())
        {
            this->deletedParticles.push_back(particle);
        }
    }
    Entity::update();
}