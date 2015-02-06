#include "FlyBootEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

FlyBootEffect::~FlyBootEffect()
{
}

bool FlyBootEffect::init()
{
    if (false == BaseEffect::initWithSpriteName("FlyBootEffect.png"))
    {
        return false;
    }
    
    this->_time = 10.0f;
    
    return true;
}

void FlyBootEffect::gameUpdate(float delta)
{
    if (nullptr == this->_effectSprite->getParent())
    {
        this->_effectSprite->setPosition(Vec2(0.0f, -260.0f));
        this->getCharacterNode()->addChild(this->_effectSprite, -10);
    }
    if (Jumping == this->getCharacterNode()->getActionState())
    {
        this->_effectSprite->setVisible(true);
    }
    else
    {
        this->_effectSprite->setVisible(false);
    }
    
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_effectSprite->setVisible(false);
    }
}

void FlyBootEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_effectSprite->setVisible(false);
}

float FlyBootEffect::changeSpeed(float speed)
{
    return speed * 1.5f;
}
