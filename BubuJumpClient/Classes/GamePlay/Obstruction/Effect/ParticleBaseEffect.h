#ifndef _ParticleBaseEffect_H_
#define _ParticleBaseEffect_H_

#include "cocos2d.h"

#include "BaseEffect.h"

class ParticleBaseEffect : public BaseEffect
{
public:
    ParticleBaseEffect(EffectType type, int grade) : BaseEffect(type, grade), _particleSystemQuad(nullptr) {};
    virtual ~ParticleBaseEffect();
    
    bool initWithParticleName(std::string particleName);
protected:
    cocos2d::ParticleSystemQuad* _particleSystemQuad;
};

#endif // _ParticleBaseEffect_H_
