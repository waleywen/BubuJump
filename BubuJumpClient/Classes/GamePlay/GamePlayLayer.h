#ifndef _GamePlayLayer_H_
#define _GamePlayLayer_H_

#include "cocos2d.h"

#include "Obstruction/ObstructionNode.h"

class CharacterNode;
class BaseEffect;

struct GamePlayData
{
    std::string typeName;
    cocos2d::Vec2 position;
    float moveDistance;
};

class GamePlayLayer : public cocos2d::Layer
{
public:
    GamePlayLayer() : _maxDistance(0), _dead(false), _visibleSize(), _origin(), _mainGameLayer(nullptr), _backgroundSprite(nullptr), _finishLineSprite(nullptr), _clearanceSprite(nullptr), _transitionNode(nullptr), _transitionLightsNode(nullptr), _lightLayerColor(nullptr), _characterNode(nullptr), _isTransiting(false), _transitionPhase(0), _lastBuildLine(0.0f), _obstructionPoolMap(), _obstructionVector(), _gamePlayDataLevelMap(), _currentPatternGamePlayDataVector(), _patternLowestLine(0.0f), _patternStartLine(0.0f) {};
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
    inline int getTransitionPhase() {return this->_transitionPhase;};

    CREATE_FUNC(GamePlayLayer);
    
    CC_SYNTHESIZE(float, _maxDistance, MaxDistance);
    CC_SYNTHESIZE(bool, _dead, Dead);
private:
    void followCharacter();
    void cleanupUselessObstructions();
    ObstructionNode* getObstructionNode(ObstructionNodeType nodeType);
    void buildTopperScene();
    
    void transitionFinished();
    
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;
    
    cocos2d::Layer* _mainGameLayer;
    cocos2d::Sprite* _backgroundSprite;
    cocos2d::Sprite* _finishLineSprite;
    cocos2d::Sprite* _clearanceSprite;
    cocos2d::Node* _transitionNode;
    cocos2d::Node* _transitionLightsNode;
    cocos2d::LayerColor* _lightLayerColor;
    CharacterNode* _characterNode;
    
    bool _isTransiting;
    int _transitionPhase;
    float _lastBuildLine;
    
    typedef typename cocos2d::Vector<ObstructionNode*> ObstructionVector;
    typedef typename std::map<ObstructionNodeType, ObstructionVector> ObstructionPoolMap;
    typedef typename std::map<ObstructionNodeType, ObstructionVector>::iterator ObstructionPoolMapIterator;
    typedef typename std::pair<ObstructionNodeType, ObstructionVector> ObstructionPoolPair;
    ObstructionPoolMap _obstructionPoolMap;
    ObstructionVector _obstructionVector;

    typedef typename std::vector<GamePlayData> GamePlayDataVector;
    typedef typename std::vector<GamePlayData>::iterator GamePlayDataVectorIter;
    typedef typename std::vector<std::vector<GamePlayData>> GamePlayDataVectors;
    typedef typename std::map<int, GamePlayDataVectors> IntGamePlayDataVectorMap;
    typedef typename std::map<int, GamePlayDataVectors>::iterator IntGamePlayDataVectorMapIter;
    typedef typename std::pair<int, GamePlayDataVectors> IntGamePlayDataVectorPair;
    
    IntGamePlayDataVectorMap _gamePlayDataLevelMap;
    GamePlayDataVector _currentPatternGamePlayDataVector;
    float _patternLowestLine;
    float _patternStartLine;
    
    void readGamePlayDataToVector(std::string csbName, GamePlayDataVector& gamePlayDataVector);
    
    float cdPlayTime;
};

#endif // _GamePlayLayer_H_
