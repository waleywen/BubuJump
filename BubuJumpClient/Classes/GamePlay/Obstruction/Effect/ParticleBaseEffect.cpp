#include "ParticleBaseEffect.h"

USING_NS_CC;

ParticleBaseEffect::~ParticleBaseEffect()
{
    if (nullptr != this->_particleSystemQuad)
    {
        this->_particleSystemQuad->release();
        this->_particleSystemQuad = nullptr;
    }
}

bool ParticleBaseEffect::initWithParticleName(std::string particleName)
{
    this->_particleSystemQuad = CCParticleSystemQuad::create(particleName);
    this->_particleSystemQuad->retain();
    this->_particleSystemQuad->setAutoRemoveOnFinish(true);
    this->_particleSystemQuad->setDuration(-1);
    
    return true;
}
