#ifndef _GameResuscitationUILayer_H_
#define _GameResuscitationUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GamePlayLayer;

class GameResuscitationUILayer : public cocos2d::Layer
{
public:
    GameResuscitationUILayer() : _countDownSprite(nullptr), _countDown(3.0f) {};
    virtual ~GameResuscitationUILayer();
    
    virtual bool init() override;
    virtual void update(float delta) override;

    CREATE_FUNC(GameResuscitationUILayer);
    
    CC_SYNTHESIZE(GamePlayLayer*, _gamePlayLayer, GamePlayLayer);
private:
    void closeButtonClicked(cocos2d::Ref* sender);
    void coinButtonClicked(cocos2d::Ref* sender);
    void qaButtonClicked(cocos2d::Ref* sender);
    
    cocos2d::Sprite* _countDownSprite;
    
    float _countDown;
};

#endif // _GameResuscitationUILayer_H_
