#include "BaseEffect.h"

#include "FlyBootEffect.h"
#include "RocketEffect.h"
#include "MagnetEffect.h"
#include "AngelWingEffect.h"
#include "EvilCloudEffect.h"
#include "VortexEffect.h"

USING_NS_CC;

BaseEffect::~BaseEffect()
{
    if (nullptr != this->_effectSprite)
    {
        this->_effectSprite->release();
        this->_effectSprite = nullptr;
    }
}

bool BaseEffect::initWithSpriteName(std::string spriteName)
{
    this->_effectSprite = Sprite::create(spriteName);
    this->_effectSprite->retain();

    return true;
}

float BaseEffect::changeSpeed(float speed)
{
    return speed;
}

float BaseEffect::changeAcceleration(float acceleration)
{
    return acceleration;
}

float BaseEffect::changeHorizontalSpeedPercentage(float percentage)
{
    return percentage;
}

bool BaseEffect::isFrozen()
{
    return false;
}

EffectFactory* EffectFactory::getInstance()
{
    static EffectFactory s_instance;
    return &s_instance;
}

BaseEffect* EffectFactory::getEffect(EffectType type, ObstructionNode* sender)
{
    for(auto& effect : this->_effectVector)
    {
        if (effect->getType() == type)
        {
            if (VortexEffectType == type)
            {
                VortexEffect* tempEffect = static_cast<VortexEffect*>(effect);
                tempEffect->setTarget(sender);
            }
            effect->reset();
            return effect;
        }
    }
    
    BaseEffect* tEffect = nullptr;
    if (FlyBootEffectType == type)
    {
        tEffect = FlyBootEffect::create();
    }
    else if (RocketEffectType == type)
    {
        tEffect = RocketEffect::create();
    }
    else if (MagnetEffectType == type)
    {
        tEffect = MagnetEffect::create();
    }
    else if (AngelWingEffectType == type)
    {
        tEffect = AngelWingEffect::create();
    }
    else if (EvilCloudEffectType == type)
    {
        tEffect = EvilCloudEffect::create();
    }
    else if (VortexEffectType == type)
    {
        VortexEffect* tempEffect = VortexEffect::create();
        tempEffect->setTarget(sender);
        tEffect = tempEffect;
    }
    
    tEffect->reset();
    this->_effectVector.pushBack(tEffect);
    return tEffect;
}