#ifndef _WeChatClient_H_
#define _WeChatClient_H_

#include <string>

class WeChatClient
{
public:
    virtual ~WeChatClient() {};
    
    virtual void sendMessage(std::string message) = 0;
};

#endif // _WeChatClient_H_
