#ifndef _MainMenuUILayer_H_
#define _MainMenuUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class MainMenuUILayer : public cocos2d::Layer
{
public:
    MainMenuUILayer() {};
    virtual ~MainMenuUILayer();
    
    virtual bool init() override;

    CREATE_FUNC(MainMenuUILayer);
    CREATE_SCENE_FUNC(MainMenuUILayer);
private:
    void playButtonClicked(cocos2d::Ref* sender);
    void taxButtonClicked(cocos2d::Ref* sender);
    void leaderboardButtonClicked(cocos2d::Ref* sender);
    void helpButtonClicked(cocos2d::Ref* sender);
    void optionButtonClicked(cocos2d::Ref* sender);
    void shareButtonClicked(cocos2d::Ref* sender);
    void drawButtonClicked(cocos2d::Ref* sender);
};

#endif // _MainMenuUILayer_H_
