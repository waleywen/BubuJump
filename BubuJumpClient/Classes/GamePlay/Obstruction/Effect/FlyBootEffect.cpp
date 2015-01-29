#include "FlyBootEffect.h"

#include "../../CharacterNode.h"

USING_NS_CC;

FlyBootEffect::~FlyBootEffect()
{
    if (nullptr != this->_flyBootEffectSprite)
    {
        this->_flyBootEffectSprite->release();
        this->_flyBootEffectSprite = nullptr;
    }
}

bool FlyBootEffect::init()
{
    if (false == BaseEffect::init())
    {
        return false;
    }
    
    this->_time = 10.0f;
    
    this->_flyBootEffectSprite = Sprite::create("FlyBootEffect.png");
    this->_flyBootEffectSprite->retain();

    return true;
}

void FlyBootEffect::gameUpdate(float delta)
{
    if (nullptr == this->_flyBootEffectSprite->getParent())
    {
        this->_flyBootEffectSprite->setPosition(Vec2(0.0f, -260.0f));
        this->getCharacterNode()->addChild(this->_flyBootEffectSprite, -10);
    }
    if (Jumping == this->getCharacterNode()->getActionState())
    {
        this->_flyBootEffectSprite->setVisible(true);
    }
    else
    {
        this->_flyBootEffectSprite->setVisible(false);
    }
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_flyBootEffectSprite->setVisible(false);
    }
}

void FlyBootEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_flyBootEffectSprite->setVisible(false);
}

float FlyBootEffect::changeSpeed(float speed)
{
    return speed * 1.5f;
}
