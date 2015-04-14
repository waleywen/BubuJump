#include "SocialManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "WeChatClientForiOS.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "WeChatClientForAndroid.h"
#endif

USING_NS_CC;

SocialManager* SocialManager::getInstance()
{
    static SocialManager s_instance;
    return &s_instance;
}

SocialManager::SocialManager() : _weChatClient(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    this->_weChatClient = new WeChatClientForiOS();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    this->_weChatClient = new WeChatClientForAndroid();
#endif
}

SocialManager::~SocialManager()
{
    delete _weChatClient;
}

void SocialManager::shareMessageToWeChat(std::string message)
{
    this->_weChatClient->sendMessage(message);
}

void SocialManager::sharePhotoToWeChat(std::string imagePath)
{
    this->_weChatClient->sendPhoto(imagePath);
}