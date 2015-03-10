#ifndef _TransitionEffect_H_
#define _TransitionEffect_H_

#include "cocos2d.h"

#include "ParticleBaseEffect.h"

class TransitionEffect : public ParticleBaseEffect
{
public:
    TransitionEffect() : ParticleBaseEffect(TransitionEffectType, 10) {};
    virtual ~TransitionEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual float changeSpeed(float speed) override;
    virtual float changeAcceleration(float acceleration) override;

    CREATE_FUNC(TransitionEffect);
};

#endif // _TransitionEffect_H_
