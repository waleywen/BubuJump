#ifndef _VortexEffect_H_
#define _VortexEffect_H_

#include "cocos2d.h"

#include "BaseEffect.h"

class ObstructionNode;

class VortexEffect : public BaseEffect
{
public:
    VortexEffect() : BaseEffect(VortexEffectType, 0), _target(nullptr) {};
    virtual ~VortexEffect();
    
    virtual bool init();
    virtual void gameUpdate(float delta) override;
    virtual void reset() override;

    virtual bool isFrozen() override;

    CREATE_FUNC(VortexEffect);
    
    CC_SYNTHESIZE(ObstructionNode*, _target, Target);
};

#endif // _VortexEffect_H_
