#ifndef _MagnetEffect_H_
#define _MagnetEffect_H_

#include "cocos2d.h"

#include "BaseEffect.h"

class MagnetEffect : public BaseEffect
{
public:
    MagnetEffect() : BaseEffect(MagnetEffectType, 0), _magnetEffectSprite(nullptr) {};
    virtual ~MagnetEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    CREATE_FUNC(MagnetEffect);
private:
    cocos2d::Sprite* _magnetEffectSprite;
};

#endif // _MagnetEffect_H_
