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
        if (std::string(pszFilePath) != "Sound/sfx-coin-pickup.wav")
        {
            AudioEngine::play2d(pszFilePath, false, this->getLowEffectVolume() ? 0.3f : 1.0f);
        }
        else
        {
            SimpleAudioEngine::getInstance()->playEffect(pszFilePath, false, 1.0 , 0.0f, this->getLowEffectVolume() ? 0.3f : 1.0f);
        }
    }
}

void AudioManager::stopAll()
{
    AudioEngine::stopAll();
}
