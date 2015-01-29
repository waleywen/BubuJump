#ifndef _FlyBootEffect_H_
#define _FlyBootEffect_H_

#include "cocos2d.h"

#include "BaseEffect.h"

class FlyBootEffect : public BaseEffect
{
public:
    FlyBootEffect() : BaseEffect(FlyBootEffectType, 0), _flyBootEffectSprite(nullptr) {};
    virtual ~FlyBootEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual float changeSpeed(float speed) override;

    CREATE_FUNC(FlyBootEffect);
private:
    cocos2d::Sprite* _flyBootEffectSprite;
};

#endif // _FlyBootEffect_H_
