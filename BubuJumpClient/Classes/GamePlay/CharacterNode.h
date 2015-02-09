#ifndef _CharacterNode_H_
#define _CharacterNode_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "GameBaseNode.h"

class ObstructionNode;
class BaseEffect;

enum CharacterMode
{
    Waiting = 0,
    Playing = 1,
};

enum CharacterActionState
{
    Idling = 0,
    Running = 1,
    Jumping = 2,
    Downing = 3,
};

struct MovingRange
{
    float start;
    float end;
};

class CharacterNode : public GameBaseNode
{
public:
    CharacterNode() : _mode(Waiting), _actionState(Idling), _maxVerticalSpeed(0), _maxHorizontalSpeed(0), _normalAcceleration(0), _horizontalMovingRange({0, 0}),  _obstructionNodeVector(nullptr), _currentSpeed(0), _horizontalSpeedPercentage(0), _characterSpriteNode(nullptr), _actionTimeline(nullptr),  _heartCount(0), _coinAmount(0), _hurtDuration(0), _effect(nullptr) {};
    virtual ~CharacterNode();
    
    virtual bool init() override;
    virtual void gameUpdate(float delta) override;
    void startPlay();
    void addHeart(int count);
    void dropHeart(int count);
    int getHeartCount();
    void addCoins(int coinCount);
    int getCoinAmount();
    void setEffect(BaseEffect* effect);
    BaseEffect* getEffect();

    CREATE_FUNC(CharacterNode);
    
    CC_SYNTHESIZE(CharacterMode, _mode, Mode);
    CC_SYNTHESIZE(CharacterActionState, _actionState, ActionState);
    CC_SYNTHESIZE(float, _maxVerticalSpeed, MaxVerticalSpeed);
    CC_SYNTHESIZE(float, _maxHorizontalSpeed, MaxHorizontalSpeed);
    CC_SYNTHESIZE(float, _normalAcceleration, NormalAcceleration);
    CC_SYNTHESIZE(MovingRange, _horizontalMovingRange, HorizontalMovingRange);
    
    CC_SYNTHESIZE(cocos2d::Vector<ObstructionNode*>*, _obstructionNodeVector, ObstructionNodeVector);
    
    CC_PROPERTY(float, _currentSpeed, CurrentSpeed);
    CC_PROPERTY(float, _horizontalSpeedPercentage, HorizontalSpeedPercentage);
private:
    float getCurrentAcceleration();
    
    void playIdleAnimation();
    void playRunAnimation();
    void playJumpAnimation();
    void playDownAnimation();

    void testAnimation(float t);

    cocos2d::Node* _characterSpriteNode;
    cocostudio::timeline::ActionTimeline* _actionTimeline;
    
    int _heartCount;
    float _coinAmount;
    float _hurtDuration;
    
    BaseEffect* _effect;
};

#endif // _CharacterNode_H_
