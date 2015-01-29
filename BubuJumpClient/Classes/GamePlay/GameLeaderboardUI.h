#ifndef _GameLeaderboardUI_H_
#define _GameLeaderboardUI_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CharacterNode;

class GameLeaderboardUI : public cocos2d::Layer
{
public:
    GameLeaderboardUI() : _loadingSprite(nullptr), _coinAmountLabel(nullptr), _distanceLabel(nullptr), _requestIndex(0) {};
    virtual ~GameLeaderboardUI();
    
    virtual bool init() override;
    void setCoinAmount(int coinAmount);
    void setMaxDistance(float maxDistance);

    CREATE_FUNC(GameLeaderboardUI);
private:
    void okButtonClicked(Ref* sender);

    void scoreSubmitted(void* resultData);
    
    cocos2d::Sprite* _loadingSprite;
    cocos2d::ui::Text* _coinAmountLabel;
    cocos2d::ui::Text* _distanceLabel;
    
    int _requestIndex;
};

#endif // _GameLeaderboardUI_H_
