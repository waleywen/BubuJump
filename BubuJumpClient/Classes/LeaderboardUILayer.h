#ifndef _LeaderboardUILayer_H_
#define _LeaderboardUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppMacros.h"

class LeaderboardUILayer : public cocos2d::Layer
{
public:
    LeaderboardUILayer() : _loadingSprite(nullptr), _taxCoinAmountLabel(nullptr), _distanceLabel(nullptr), _requestIndex(0) {};
    virtual ~LeaderboardUILayer();
    
    virtual bool init() override;
    void setTaxCoinAmount(int taxCoinAmount);
    void setMaxDistance(float maxDistance);

    CREATE_FUNC(LeaderboardUILayer);
    CREATE_SCENE_FUNC(LeaderboardUILayer);
private:
    void okButtonClicked(Ref* sender);
    void homeButtonClicked(Ref* sender);

    void scoreSubmitted(void* resultData);
    
    cocos2d::Sprite* _loadingSprite;
    cocos2d::ui::Text* _taxCoinAmountLabel;
    cocos2d::ui::Text* _distanceLabel;
    
    int _requestIndex;
};

#endif // _LeaderboardUILayer_H_
