#ifndef _AngelWingEffect_H_
#define _AngelWingEffect_H_

#include "cocos2d.h"

#include "SpriteBaseEffect.h"

class AngelWingEffect : public SpriteBaseEffect
{
public:
    AngelWingEffect() : SpriteBaseEffect(AngelWingEffectType, 0) {};
    virtual ~AngelWingEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual float changeAcceleration(float acceleration) override;

    CREATE_FUNC(AngelWingEffect);
};

#endif // _AngelWingEffect_H_
