#include "RocketEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

RocketEffect::~RocketEffect()
{
}

bool RocketEffect::init()
{
    if (false == ParticleBaseEffect::initWithParticleName("RocketEffect.plist"))
    {
        return false;
    }
    
    this->_time = 4.0f;
    
    return true;
}

void RocketEffect::gameUpdate(float delta)
{
    if (nullptr == this->_particleSystemQuad->getParent())
    {
        this->_particleSystemQuad->setPosition(Vec2(0.0f, -100.0f));
        this->getCharacterNode()->addChild(this->_particleSystemQuad, -10);
    }
    
    if (false == this->_particleSystemQuad->isActive())
    {
        this->_particleSystemQuad->resetSystem();
    }
    
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_particleSystemQuad->stopSystem();
    }
}

void RocketEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_particleSystemQuad->stopSystem();
}

float RocketEffect::changeSpeed(float speed)
{
    return 1500.0f;
}

float RocketEffect::changeAcceleration(float acceleration)
{
    return 0.0f;
}
