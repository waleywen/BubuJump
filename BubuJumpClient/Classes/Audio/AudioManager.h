#ifndef _AudioManager_H_
#define _AudioManager_H_

#include "cocos2d.h"

#include "AppMacros.h"

class AudioManager
{
public:
    static AudioManager* getInstance();
    
    AudioManager() : _lowEffectVolume(false) {};
    
    void playBackgroundMusic(const char* pszFilePath, bool bLoop);
    void playEffect(const char* pszFilePath);
    void stopAll();
    
    CC_SYNTHESIZE(bool, _lowEffectVolume, LowEffectVolume);
};

#endif // _AudioManager_H_
