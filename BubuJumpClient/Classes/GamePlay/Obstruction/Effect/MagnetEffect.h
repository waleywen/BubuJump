#ifndef _MagnetEffect_H_
#define _MagnetEffect_H_

#include "cocos2d.h"

#include "SpriteBaseEffect.h"

class MagnetEffect : public SpriteBaseEffect
{
public:
    MagnetEffect() : SpriteBaseEffect(MagnetEffectType, 0) {};
    virtual ~MagnetEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    CREATE_FUNC(MagnetEffect);
};

#endif // _MagnetEffect_H_
