#ifndef _GamePlayUILayer_H_
#define _GamePlayUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CharacterNode;
class BaseEffect;

class GamePlayUILayer : public cocos2d::Layer
{
public:
    GamePlayUILayer() : _heartCount(0), _coinAmount(0), _maxDistance(0), _effect(nullptr), _coinAmountLabel(nullptr), _heartLabel(nullptr), _distanceLabel(nullptr), _propSprite(nullptr), _currentCoinAmount(0), _currentDistance(0) {};
    virtual ~GamePlayUILayer();
    
    virtual bool init() override;
    void gameUpdate(float delta);

    CREATE_FUNC(GamePlayUILayer);

    CC_SYNTHESIZE(int, _heartCount, HeartCount);
    CC_SYNTHESIZE(int, _coinAmount, CoinAmount);
    CC_SYNTHESIZE(float, _maxDistance, MaxDistance);
    CC_SYNTHESIZE(BaseEffect*, _effect, Effect);

private:
    void pauseButtonClicked(Ref* sender);

    cocos2d::ui::Text* _coinAmountLabel;
    cocos2d::ui::Text* _heartLabel;
    cocos2d::ui::Text* _distanceLabel;

    cocos2d::Sprite* _propSprite;

    int _currentCoinAmount;
    float _currentDistance;
};

#endif // _GamePlayUILayer_H_
