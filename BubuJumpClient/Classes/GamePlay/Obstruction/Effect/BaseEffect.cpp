#include "BaseEffect.h"

#include "FlyBootEffect.h"
#include "RocketEffect.h"
#include "MagnetEffect.h"
#include "AngelWingEffect.h"
#include "EvilCloudEffect.h"
#include "VortexEffect.h"
#include "TransitionEffect.h"

USING_NS_CC;

BaseEffect::~BaseEffect()
{

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
    else if (TransitionEffectType == type)
    {
        tEffect = TransitionEffect::create();
    }
    
    tEffect->reset();
    this->_effectVector.pushBack(tEffect);
    return tEffect;
}