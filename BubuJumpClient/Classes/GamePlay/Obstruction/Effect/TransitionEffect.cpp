#include "TransitionEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

TransitionEffect::~TransitionEffect()
{
}

bool TransitionEffect::init()
{
    if (false == ParticleBaseEffect::initWithParticleName("RocketEffect.plist"))
    {
        return false;
    }
    
    this->_time = 10.0f;
//    this->_time = FileUtils::getInstance()->getValueVectorFromFile("/mnt/sdcard/BubuJump/Duration.plist").at(0).asInt();
    
    return true;
}

void TransitionEffect::gameUpdate(float delta)
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

void TransitionEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_particleSystemQuad->stopSystem();
}

float TransitionEffect::changeSpeed(float speed)
{
    return 1500.0f;
}

float TransitionEffect::changeAcceleration(float acceleration)
{
    return 0.0f;
}
