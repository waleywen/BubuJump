#ifndef _WeChatClientForAndroid_H_
#define _WeChatClientForAndroid_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "WeChatClient.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"

class WeChatClientForAndroid : public WeChatClient
{
public:
    WeChatClientForAndroid();
    virtual ~WeChatClientForAndroid();
    
    virtual void sendMessage(std::string message) override;
private:
    cocos2d::JniMethodInfo _info;
    jobject _javaClient;
};

#endif

#endif // _WeChatClientForAndroid_H_
