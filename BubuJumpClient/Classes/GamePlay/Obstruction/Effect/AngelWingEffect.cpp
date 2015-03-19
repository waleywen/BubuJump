#include "AngelWingEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

AngelWingEffect::~AngelWingEffect()
{
}

bool AngelWingEffect::init()
{
    if (false == SpriteBaseEffect::initWithSpriteName("AngelWingEffect.png"))
    {
        return false;
    }
    
    this->_time = 4.0f;
    
    return true;
}

void AngelWingEffect::gameUpdate(float delta)
{
    if (nullptr == this->_effectSprite->getParent())
    {
        this->_effectSprite->setPosition(Vec2(0.0f, 0.0f));
        this->getCharacterNode()->addChild(this->_effectSprite, -10);
    }
    if (Downing == this->getCharacterNode()->getActionState())
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

void AngelWingEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_effectSprite->setVisible(false);
}

float AngelWingEffect::changeAcceleration(float acceleration)
{
    if (Downing == this->getCharacterNode()->getActionState())
    {
        return acceleration * 0.3f;
    }
    else
    {
        return acceleration;
    }
}
