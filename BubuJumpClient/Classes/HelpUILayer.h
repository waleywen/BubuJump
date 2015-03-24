#ifndef _HelpUILayer_H_
#define _HelpUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class HelpUILayer : public cocos2d::Layer
{
public:
    HelpUILayer() : _pageNode1(nullptr), _pageNode2(nullptr), _pageNode3(nullptr), _pageNode4(nullptr), _lotteryNode(nullptr), _leftArrowButton(nullptr), _rightArrowButton(nullptr), _nameEditBox(nullptr), _phoneEditBox(nullptr), _currentPageIndex(0) {};
    virtual ~HelpUILayer();
    
    virtual bool init() override;

    CREATE_FUNC(HelpUILayer);
    CREATE_SCENE_FUNC(HelpUILayer);
private:
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void backButtonClicked(Ref* sender);
    void leftArrowButtonClicked(Ref* sender);
    void rightArrowButtonClicked(Ref* sender);
    void confirmButtonClicked(Ref* sender);

    void showPage(int index);
    
    void textFieldTapped(cocos2d::Ref*, cocos2d::ui::TextField::EventType eventType);
    
    cocos2d::Node* _pageNode1;
    cocos2d::Node* _pageNode2;
    cocos2d::Node* _pageNode3;
    cocos2d::Node* _pageNode4;
    cocos2d::Node* _lotteryNode;
    cocos2d::ui::Button* _leftArrowButton;
    cocos2d::ui::Button* _rightArrowButton;
    cocos2d::ui::Widget* _nameEditBox;
    cocos2d::ui::Widget* _phoneEditBox;
    
    int _currentPageIndex;
    
    cocos2d::Point _beginPoint;
    cocos2d::Point _endPoint;
};

#endif // _HelpUILayer_H_
