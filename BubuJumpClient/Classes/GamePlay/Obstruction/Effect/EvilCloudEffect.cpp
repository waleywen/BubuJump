#include "EvilCloudEffect.h"

#include "../../CharacterNode.h"
#include "../ObstructionNode.h"

USING_NS_CC;

EvilCloudEffect::~EvilCloudEffect()
{
}

bool EvilCloudEffect::init()
{
    if (false == SpriteBaseEffect::initWithSpriteName("EvilCloudEffect.png"))
    {
        return false;
    }
    
    this->_time = 10.0f;
    
    return true;
}

void EvilCloudEffect::gameUpdate(float delta)
{
    if (nullptr == this->_effectSprite->getParent())
    {
        this->_effectSprite->setPosition(Vec2(0.0f, 50.0f));
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

void EvilCloudEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_effectSprite->setVisible(false);
}

float EvilCloudEffect::changeHorizontalSpeedPercentage(float percentage)
{
    return percentage * -1.0f;
}
