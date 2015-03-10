#ifndef _JoinLotteryUILayer_H_
#define _JoinLotteryUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class JoinLotteryUILayer : public cocos2d::Layer
{
public:
    JoinLotteryUILayer() : _nameEditBox(nullptr), _phoneEditBox(nullptr), _backLayerColor(nullptr) {};
    virtual ~JoinLotteryUILayer();
    
    virtual bool init() override;

    CREATE_FUNC(JoinLotteryUILayer);
private:
    void closeButtonClicked(Ref* sender);
    void submitButtonClicked(Ref* sender);
    void waitButtonClicked(Ref* sender);
    void changeButtonClicked(Ref* sender);
    
    void textFieldTapped(cocos2d::Ref*, cocos2d::ui::TextField::EventType eventType);

    cocos2d::ui::Widget* _nameEditBox;
    cocos2d::ui::Widget* _phoneEditBox;

    cocos2d::LayerColor* _backLayerColor;
};

#endif // _JoinLotteryUILayer_H_
