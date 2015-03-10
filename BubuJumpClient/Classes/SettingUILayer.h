#ifndef _SettingUILayer_H_
#define _SettingUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class SettingUILayer : public cocos2d::Layer
{
public:
    SettingUILayer() {};
    virtual ~SettingUILayer();
    
    virtual bool init() override;

    CREATE_FUNC(SettingUILayer);
    CREATE_SCENE_FUNC(SettingUILayer);
private:
    void backButtonClicked(Ref* sender);
    void soundButtonClicked(cocos2d::Ref* sender);
    void musicButtonClicked(cocos2d::Ref* sender);
};

#endif // _SettingUILayer_H_
