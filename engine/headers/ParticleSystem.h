#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#pragma once
#include "vector"
#include "algorithm"

class ParticleSystem : public Entity
{
    public:
        std::vector<Particle*> particles;
        std::vector<Particle*> deletedParticles;
        ParticleData particleData;

        ParticleSystem(ParticleData particleData);
        void addParticle();
        void addSpecificParticle(ParticleData particleData);
        void removeParticles();
        void setParticleData(ParticleData particleData);
        virtual void update() override;
};

#endif