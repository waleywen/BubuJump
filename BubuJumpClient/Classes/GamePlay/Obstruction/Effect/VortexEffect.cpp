#include "VortexEffect.h"

#include "../../CharacterNode.h"
#include "../ObstructionNode.h"

USING_NS_CC;

VortexEffect::~VortexEffect()
{
}

bool VortexEffect::init()
{
    if (false == SpriteBaseEffect::initWithSpriteName("VortexEffect.png"))
    {
        return false;
    }
    
    return true;
}

void VortexEffect::gameUpdate(float delta)
{
    if (nullptr == this->_effectSprite->getParent())
    {
        this->_effectSprite->setPosition(Vec2(0.0f, 0.0f));
        this->getCharacterNode()->addChild(this->_effectSprite, -10);
    }
    this->_effectSprite->setVisible(true);
    
    static const float movingSpeed = 500.0f;
    Point targetPosition = this->getTarget()->getPosition();
    Point characterNodePosition = this->getCharacterNode()->getPosition();
    Point newPosition = characterNodePosition - ((characterNodePosition - targetPosition) * (delta * movingSpeed / (characterNodePosition - targetPosition).length()));
    if ((newPosition - characterNodePosition).length() > (targetPosition - characterNodePosition).length())
    {
        newPosition = targetPosition;
        
        this->getCharacterNode()->setCurrentSpeed(this->getCharacterNode()->getMaxVerticalSpeed());
        this->getCharacterNode()->dropHeart(1);
        
        this->getTarget()->setState(InactivatedNodeState);
        this->setState(InactivatedEffectState);
        this->_effectSprite->setVisible(false);
    }
    this->getCharacterNode()->setPosition(newPosition);
    
    this->setDuration(2.6f);
}

void VortexEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_effectSprite->setVisible(false);
}

bool VortexEffect::isFrozen()
{
    return true;
}
