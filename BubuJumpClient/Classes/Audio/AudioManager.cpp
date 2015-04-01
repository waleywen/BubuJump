#include "AudioManager.h"

#include "audio/include/SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"

#include "UIHelper.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace experimental;

AudioManager* AudioManager::getInstance()
{
    static AudioManager s_instance;
    return &s_instance;
}

void AudioManager::playBackgroundMusic(const char *pszFilePath, bool bLoop)
{
//    if (SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() > 0.5)
    {
//        AudioEngine::play2d(pszFilePath, bLoop);
        SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath, true);
    }
}

void AudioManager::playEffect(const char *pszFilePath)
{
    if (SimpleAudioEngine::getInstance()->getEffectsVolume() > 0.5)
    {
//        AudioEngine::play2d(pszFilePath);
        SimpleAudioEngine::getInstance()->playEffect(pszFilePath);
    }
}

void AudioManager::stopAll()
{
    AudioEngine::stopAll();
}
