#ifndef _GamePlayScene_H_
#define _GamePlayScene_H_

#include "cocos2d.h"

class GamePlayLayer;
class GamePlayUILayer;

class GamePlayScene : public cocos2d::Scene
{
public:
    GamePlayScene() : _gamePlayLayer(nullptr), _gamePlayUILayer(nullptr) {};
    ~GamePlayScene();
    
    virtual bool init() override;
    virtual void update(float delta) override;

    CREATE_FUNC(GamePlayScene);
  
    CC_SYNTHESIZE_READONLY(GamePlayLayer*, _gamePlayLayer, GamePlayLayerLayer);
    CC_SYNTHESIZE_READONLY(GamePlayUILayer*, _gamePlayUILayer, GamePlayUILayer);
};

#endif // _GamePlayScene_H_
