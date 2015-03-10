#ifndef _GameLeaderboardUI_H_
#define _GameLeaderboardUI_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Obstruction/ObstructionNode.h"

class GameOverUILayer : public cocos2d::Layer
{
public:
    GameOverUILayer() : _loadingSprite(nullptr), _taxCoinAmountLabel(nullptr), _distanceLabel(nullptr), _myNameLabel(nullptr), _requestIndex(0) {};
    virtual ~GameOverUILayer();
    
    virtual bool init() override;
    virtual void update(float delta) override;

    void setTaxCoinAmount(int taxCoinAmount);
    void setMaxDistance(float maxDistance);
    void setTaxCoinMap(const TaxCoinMap& taxCoinMap);

    CREATE_FUNC(GameOverUILayer);
private:
    void shareButtonClicked(Ref* sender);
    void retryButtonClicked(Ref* sender);
    void homeButtonClicked(cocos2d::Ref* sender);

    void scoreSubmitted(void* resultData);
    
    cocos2d::Sprite* _loadingSprite;
    cocos2d::ui::Text* _taxCoinAmountLabel;
    cocos2d::ui::Text* _distanceLabel;
    
    cocos2d::ui::Text* _myNameLabel;

    int _requestIndex;
};

#endif // _GameLeaderboardUI_H_
