#ifndef _BaseEffect_H_
#define _BaseEffect_H_

#include "cocos2d.h"

class CharacterNode;

enum EffectType
{
    NoneEffectType,
    FlyBootEffectType,
    RocketEffectType,
    MagnetEffectType,
};

enum EffectState
{
    InactivatedEffectState,
    ActivatedEffectState,
};

class BaseEffect : public cocos2d::Ref
{
public:
    BaseEffect(EffectType type, int grade) : _type(type), _grade(grade), _time(0), _duration(0), _state(ActivatedEffectState) {};
    virtual ~BaseEffect() = 0;
    
    virtual bool init();
    virtual void gameUpdate(float delta) = 0;
    virtual void reset() = 0;
    
    virtual float changeSpeed(float speed);
    virtual float changeAcceleration(float acceleration);

    CC_SYNTHESIZE(EffectType, _type, Type);
    CC_SYNTHESIZE(int, _grade, Grade);
    CC_SYNTHESIZE(float, _time, Time);
    CC_SYNTHESIZE(float, _duration, Duration);
    CC_SYNTHESIZE(EffectState, _state, State);
    
    CC_SYNTHESIZE(CharacterNode*, _characterNode, CharacterNode);
};

class EffectFactory
{
public:
    static EffectFactory* getInstance();
    
    BaseEffect* getEffect(EffectType type);
    
private:
    cocos2d::Vector<BaseEffect*> _effectVector;
};

#endif // _BaseEffect_H_
