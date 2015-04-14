#ifndef _WeChatClient_H_
#define _WeChatClient_H_

#include <string>

class WeChatClient
{
public:
    virtual ~WeChatClient() {};
    
    virtual void sendMessage(std::string message) = 0;
    virtual void sendPhoto(std::string imagePath) = 0;
};

#endif // _WeChatClient_H_
