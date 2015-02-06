#include "RocketEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

RocketEffect::~RocketEffect()
{
}

bool RocketEffect::init()
{
    if (false == BaseEffect::initWithSpriteName("RocketEffect.png"))
    {
        return false;
    }
    
    this->_time = 4.0f;
    
    return true;
}

void RocketEffect::gameUpdate(float delta)
{
    if (nullptr == this->_effectSprite->getParent())
    {
        this->_effectSprite->setPosition(Vec2(0.0f, -200.0f));
        this->getCharacterNode()->addChild(this->_effectSprite, -10);
    }
    this->_effectSprite->setVisible(true);
    
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_effectSprite->setVisible(false);
    }
}

void RocketEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_effectSprite->setVisible(false);
}

float RocketEffect::changeSpeed(float speed)
{
    return this->getCharacterNode()->getMaxVerticalSpeed() * 1.5f;
}

float RocketEffect::changeAcceleration(float acceleration)
{
    return 0.0f;
}
