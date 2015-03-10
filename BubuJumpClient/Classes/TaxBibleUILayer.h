#ifndef _TaxBibleUILayer_H_
#define _TaxBibleUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class TaxBibleContentUILayer : public cocos2d::Layer
{
public:
    TaxBibleContentUILayer() : _scrollView(nullptr), _contentLabel(nullptr) {};
    virtual ~TaxBibleContentUILayer();
    
    virtual bool init() override;
    void setContentString(std::string contentString);
    
    CREATE_FUNC(TaxBibleContentUILayer);
    CREATE_SCENE_FUNC(TaxBibleContentUILayer);
private:
    void backButtonClicked(Ref* sender);
    
    cocos2d::ui::ScrollView* _scrollView;
    cocos2d::ui::Text* _contentLabel;
};

class TaxBibleUILayer : public cocos2d::Layer
{
public:
    TaxBibleUILayer() {};
    virtual ~TaxBibleUILayer();
    
    virtual bool init() override;

    CREATE_FUNC(TaxBibleUILayer);
    CREATE_SCENE_FUNC(TaxBibleUILayer);
private:
    void backButtonClicked(Ref* sender);
    void taxButtonClicked(Ref* sender);
};

#endif // _TaxBibleUILayer_H_
