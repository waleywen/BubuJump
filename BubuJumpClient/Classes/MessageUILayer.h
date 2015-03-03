#ifndef _MessageUILayer_H_
#define _MessageUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class MessageUILayer : public cocos2d::Layer
{
public:
    static MessageUILayer* create(float autoCloseDuration, cocos2d::Node* parent, std::string spriteName);
    static MessageUILayer* create(float autoCloseDuration, cocos2d::Node* parent, std::string text, const cocos2d::Size& backgroundSize);

    MessageUILayer() : _autoCloseDuration(0.0f), _duration(0.0f) {};
    virtual ~MessageUILayer();
    
    bool initWithDurationAndParent(float autoCloseDuration, cocos2d::Node* parent);
    virtual void update(float delta) override;
private:
    float _autoCloseDuration;
    
    float _duration;
};

#endif // _MessageUILayer_H_
