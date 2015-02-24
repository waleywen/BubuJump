#ifndef _RocketEffect_H_
#define _RocketEffect_H_

#include "cocos2d.h"

#include "ParticleBaseEffect.h"

class RocketEffect : public ParticleBaseEffect
{
public:
    RocketEffect() : ParticleBaseEffect(RocketEffectType, 1) {};
    virtual ~RocketEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual float changeSpeed(float speed) override;
    virtual float changeAcceleration(float acceleration) override;

    CREATE_FUNC(RocketEffect);
};

#endif // _FlyBootEffect_H_
