#ifndef _GamePlayLayer_H_
#define _GamePlayLayer_H_

#include "cocos2d.h"

#include "Obstruction/ObstructionNode.h"

class CharacterNode;
class BaseEffect;

class GamePlayLayer : public cocos2d::Layer
{
public:
    GamePlayLayer() : _maxDistance(0), _dead(false), _visibleSize(), _origin(), _mainGameLayer(nullptr), _transitionBackgroundSprite(nullptr), _characterNode(nullptr), _transitionPhase(0), _lastBuildLine(0.0f), _obstructionPoolMap(), _obstructionVector() {};
    virtual ~GamePlayLayer();
    
    virtual bool init() override;
    void gameUpdate(float delta);
    void accelerated(cocos2d::Acceleration* acceleration, cocos2d::Event* event);
    
    void startPlay();
    void revive(int coinCount);
    
    int getHeartCount();
    int getCoinAmount();
    int getTaxCoinAmount();;
    const TaxCoinMap& getTaxCoinMap();
    BaseEffect* getEffect();

    CREATE_FUNC(GamePlayLayer);
    
    CC_SYNTHESIZE(float, _maxDistance, MaxDistance);
    CC_SYNTHESIZE(bool, _dead, Dead);
private:
    void followCharacter();
    void cleanupUselessObstructions();
    ObstructionNode* getObstructionNode(ObstructionNodeType nodeType);
    void buildTopperScene();
    
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;
    
    cocos2d::Layer* _mainGameLayer;
    cocos2d::Sprite* _transitionBackgroundSprite;
    CharacterNode* _characterNode;
    
    int _transitionPhase;
    float _lastBuildLine;
    
    typedef typename cocos2d::Vector<ObstructionNode*> ObstructionVector;
    typedef typename std::map<ObstructionNodeType, ObstructionVector> ObstructionPoolMap;
    typedef typename std::map<ObstructionNodeType, ObstructionVector>::iterator ObstructionPoolMapIterator;
    typedef typename std::pair<ObstructionNodeType, ObstructionVector> ObstructionPoolPair;
    ObstructionPoolMap _obstructionPoolMap;
    ObstructionVector _obstructionVector;

    float cdPlayTime;
};

#endif // _GamePlayLayer_H_
