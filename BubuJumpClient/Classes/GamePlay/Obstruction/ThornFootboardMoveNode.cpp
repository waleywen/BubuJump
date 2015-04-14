#include "ThornFootboardMoveNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;
using namespace CocosDenshion;

ThornFootboardMoveNode::~ThornFootboardMoveNode()
{

}

bool ThornFootboardMoveNode::init()
{
    if (false == ObstructionNode::initWithCsbName("ThornFootboardMoveNode.csb"))
    {
        return false;
    }
    
    return true;
}

void ThornFootboardMoveNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->dropHeart(3);
    this->setVisible(false);

    if (nullptr == characterNode->getEffect() || InactivatedEffectState == characterNode->getEffect()->getState() || RocketEffectType != characterNode->getEffect()->getType())
    {
        AudioManager::getInstance()->playEffect("Sound/sfx-thorn-footboard.aac");
    }
}

void ThornFootboardMoveNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}

void ThornFootboardMoveNode::moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint)
{
    static const float moveSpeed = 50.0f;
    
    this->stopAllActions();
    float duration = (startPoint - endPoint).length() / moveSpeed / 2.0f;
    this->setPosition(startPoint);
    auto moveTo1 = MoveTo::create(duration, endPoint);
    auto moveTo2 = MoveTo::create(duration, startPoint);
    this->runAction(Repeat::create(Sequence::create(moveTo1, moveTo2, nullptr), pow(2,30)));
}
