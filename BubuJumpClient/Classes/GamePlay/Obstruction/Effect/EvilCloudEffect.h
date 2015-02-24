#ifndef _EvilCloudEffect_H_
#define _EvilCloudEffect_H_

#include "cocos2d.h"

#include "SpriteBaseEffect.h"

class EvilCloudEffect : public SpriteBaseEffect
{
public:
    EvilCloudEffect() : SpriteBaseEffect(EvilCloudEffectType, 0) {};
    virtual ~EvilCloudEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual float changeHorizontalSpeedPercentage(float percentage) override;

    CREATE_FUNC(EvilCloudEffect);
};

#endif // _EvilCloudEffect_H_
