#include "MessageUILayer.h"

#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

MessageUILayer* MessageUILayer::create(float autoCloseDuration, cocos2d::Node *parent, std::string spriteName)
{
    MessageUILayer* pRet = new (std::nothrow) MessageUILayer();
    
    if (pRet != nullptr && pRet->initWithDurationAndParent(autoCloseDuration, parent))
    {
        pRet->autorelease();
        
        auto sprite = Sprite::create(spriteName);
        sprite->setPosition(Point(designResolutionSize.width / 2.0f, designResolutionSize.height / 2.0f));
        pRet->addChild(sprite);
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

MessageUILayer* MessageUILayer::create(float autoCloseDuration, cocos2d::Node *parent, std::string text, const cocos2d::Size& backgroundSize)
{
    MessageUILayer* pRet = new (std::nothrow) MessageUILayer();
    
    if (pRet != nullptr && pRet->initWithDurationAndParent(autoCloseDuration, parent))
    {
        pRet->autorelease();
        
        auto scale9Sprite = Scale9Sprite::create(Rect(11.0f, 13.0f, 1.0f, 1.0f), "GameTaxQAUIResultBackground.png");
        scale9Sprite->setPosition(Point(designResolutionSize.width / 2.0f, designResolutionSize.height / 2.0f));
        scale9Sprite->setContentSize(backgroundSize);
        pRet->addChild(scale9Sprite);
    
        auto label = Text::create();
        label->setString(text);
        label->setPosition(scale9Sprite->getPosition());
        label->setFontSize(50);
        pRet->addChild(label);
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

MessageUILayer::~MessageUILayer()
{
}

bool MessageUILayer::initWithDurationAndParent(float autoCloseDuration, cocos2d::Node *parent)
{
    if (false == Layer::init())
    {
        return false;
    }
    
    this->_autoCloseDuration = autoCloseDuration;
    
    parent->addChild(this);
    
    auto backLayerColor = LayerColor::create(Color4B(166, 166, 166, 128), designResolutionSize.width, designResolutionSize.height);
    auto resultNodeEventListener = EventListenerTouchOneByOne::create();
    resultNodeEventListener->setSwallowTouches(true);
    resultNodeEventListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        event->getCurrentTarget()->getParent()->removeFromParent();
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(resultNodeEventListener, backLayerColor);
    this->addChild(backLayerColor, -1);
    
    this->scheduleUpdate();
    
    return true;
}

void MessageUILayer::update(float delta)
{
    this->_duration += delta;
    if (this->_duration >= this->_autoCloseDuration)
    {
        this->removeFromParent();
    }
}
