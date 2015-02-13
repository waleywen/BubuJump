#ifndef _GamePauseUILayer_H_
#define _GamePauseUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GamePauseUILayer : public cocos2d::Layer
{
public:
    GamePauseUILayer() : _coinAmountLabel(nullptr), _distanceLabel(nullptr) {};
    virtual ~GamePauseUILayer();
    
    virtual bool init() override;
    void setCoinAmount(int coinAmount);
    void setMaxDistance(float maxDistance);

    CREATE_FUNC(GamePauseUILayer);
private:
    void continueButtonClicked(cocos2d::Ref* sender);
    void homeButtonClicked(cocos2d::Ref* sender);

    cocos2d::ui::Text* _coinAmountLabel;
    cocos2d::ui::Text* _distanceLabel;
};

#endif // _GamePauseUILayer_H_
