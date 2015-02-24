#ifndef _SpriteBaseEffect_H_
#define _SpriteBaseEffect_H_

#include "cocos2d.h"

#include "BaseEffect.h"

class SpriteBaseEffect : public BaseEffect
{
public:
    SpriteBaseEffect(EffectType type, int grade) : BaseEffect(type, grade), _effectSprite(nullptr) {};
    virtual ~SpriteBaseEffect();
    
    bool initWithSpriteName(std::string spriteName);
protected:
    cocos2d::Sprite* _effectSprite;
};

#endif // _SpriteBaseEffect_H_
