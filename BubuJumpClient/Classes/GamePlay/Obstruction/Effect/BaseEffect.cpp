#include "BaseEffect.h"

#include "FlyBootEffect.h"
#include "RocketEffect.h"
#include "MagnetEffect.h"

USING_NS_CC;

BaseEffect::~BaseEffect()
{
}

bool BaseEffect::init()
{
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

EffectFactory* EffectFactory::getInstance()
{
    static EffectFactory s_instance;
    return &s_instance;
}

BaseEffect* EffectFactory::getEffect(EffectType type)
{
    for(auto& effect : this->_effectVector)
    {
        if (effect->getType() == type)
        {
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
    tEffect->reset();
    this->_effectVector.pushBack(tEffect);
    return tEffect;
}