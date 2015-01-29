#include "RocketEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

RocketEffect::~RocketEffect()
{
    if (nullptr != this->_rocketEffectSprite)
    {
        this->_rocketEffectSprite->release();
        this->_rocketEffectSprite = nullptr;
    }
}

bool RocketEffect::init()
{
    if (false == BaseEffect::init())
    {
        return false;
    }
    
    this->_time = 4.0f;
    
    this->_rocketEffectSprite = Sprite::create("RocketEffect.png");
    this->_rocketEffectSprite->retain();
    
    return true;
}

void RocketEffect::gameUpdate(float delta)
{
    if (nullptr == this->_rocketEffectSprite->getParent())
    {
        this->_rocketEffectSprite->setPosition(Vec2(0.0f, -200.0f));
        this->getCharacterNode()->addChild(this->_rocketEffectSprite, -10);
    }
    this->_rocketEffectSprite->setVisible(true);
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_rocketEffectSprite->setVisible(false);
    }
}

void RocketEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_rocketEffectSprite->setVisible(false);
}

float RocketEffect::changeSpeed(float speed)
{
    return this->getCharacterNode()->getMaxVerticalSpeed() * 1.5f;
}

float RocketEffect::changeAcceleration(float acceleration)
{
    return 0.0f;
}
