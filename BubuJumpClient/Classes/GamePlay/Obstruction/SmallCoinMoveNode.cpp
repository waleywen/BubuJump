#include "SmallCoinMoveNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

SmallCoinMoveNode::~SmallCoinMoveNode()
{

}

bool SmallCoinMoveNode::init()
{
    if (false == ObstructionNode::initWithCsbName("SmallCoinMoveNode.csb"))
    {
        return false;
    }
    
    return true;
}

void SmallCoinMoveNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->addCoins(10, this->getNodeType());
    this->setVisible(false);

    AudioManager::getInstance()->playEffect("Sound/sfx-coin-pickup.wav");
}

void SmallCoinMoveNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}

void SmallCoinMoveNode::moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint)
{
    static const float moveSpeed = 50.0f;
    
    this->stopAllActions();
    float duration = (startPoint - endPoint).length() / moveSpeed / 2.0f;
    this->setPosition(startPoint);
    auto moveTo1 = MoveTo::create(duration, endPoint);
    auto moveTo2 = MoveTo::create(duration, startPoint);
    this->runAction(Repeat::create(Sequence::create(moveTo1, moveTo2, nullptr), pow(2,30)));
}
