#ifndef _WeChatClientForiOS_H_
#define _WeChatClientForiOS_H_

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "WeChatClient.h"

class WeChatClientForiOS : public WeChatClient
{
public:
    virtual ~WeChatClientForiOS() {};
    
    virtual void sendMessage(std::string message) override {};
};

#endif

#endif // _WeChatClientForiOS_H_
