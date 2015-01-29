#ifndef _RocketEffect_H_
#define _RocketEffect_H_

#include "cocos2d.h"

#include "BaseEffect.h"

class RocketEffect : public BaseEffect
{
public:
    RocketEffect() : BaseEffect(RocketEffectType, 1), _rocketEffectSprite(nullptr) {};
    virtual ~RocketEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual float changeSpeed(float speed) override;
    virtual float changeAcceleration(float acceleration) override;

    CREATE_FUNC(RocketEffect);
private:
    cocos2d::Sprite* _rocketEffectSprite;
};

#endif // _FlyBootEffect_H_
