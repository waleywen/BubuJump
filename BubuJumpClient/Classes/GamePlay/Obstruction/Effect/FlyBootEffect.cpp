#include "FlyBootEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

FlyBootEffect::~FlyBootEffect()
{
}

bool FlyBootEffect::init()
{
    if (false == ParticleBaseEffect::initWithParticleName("FlyBootEffect.plist"))
    {
        return false;
    }
    
    this->_time = 10.0f;
    
    return true;
}

void FlyBootEffect::gameUpdate(float delta)
{
    if (nullptr == this->_particleSystemQuad->getParent())
    {
        this->_particleSystemQuad->setPosition(Vec2(0.0f, -100.0f));
        this->getCharacterNode()->addChild(this->_particleSystemQuad, -10);
    }
    if (Jumping == this->getCharacterNode()->getActionState())
    {
        if (false == this->_particleSystemQuad->isActive())
        {
            this->_particleSystemQuad->resetSystem();
        }
    }
    else
    {
        if (true == this->_particleSystemQuad->isActive())
        {
            this->_particleSystemQuad->stopSystem();
        }
    }
    
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_particleSystemQuad->stopSystem();
    }
}

void FlyBootEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_particleSystemQuad->stopSystem();
}

float FlyBootEffect::changeSpeed(float speed)
{
    return speed * 1.5f;
}
