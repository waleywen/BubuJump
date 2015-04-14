#ifndef _SocialManager_H_
#define _SocialManager_H_

#include <string>
#include "cocos2d.h"

class WeChatClient;

class SocialManager
{
public:
    static SocialManager* getInstance();
    
    SocialManager();
    ~SocialManager();
    
    void shareMessageToWeChat(std::string message);
    void sharePhotoToWeChat(std::string imagePath);
private:
    WeChatClient* _weChatClient;
};

#endif // _SocialManager_H_
