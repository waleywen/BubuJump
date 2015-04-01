#include "FootboardMoveNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

FootboardMoveNode::~FootboardMoveNode()
{

}

bool FootboardMoveNode::init()
{
    if (false == ObstructionNode::initWithCsbName("FootboardMoveNode.csb"))
    {
        return false;
    }
    
    return true;
}

void FootboardMoveNode::collided(CharacterNode *characterNode)
{
    if (Downing == characterNode->getActionState())
    {
        float v = characterNode->getCurrentSpeed();
        float a = -1000;
        float distance = -(v * v / 2.0f / a);
        if (characterNode->getPosition().y + distance - this->getPosition().y > (this->getCollisionSize().height + characterNode->getCollisionSize().height) / 2.0f)
        {
            characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
            
            AudioManager::getInstance()->playEffect("Sound/sfx-footboard-move.wav");
        }
    }
}

void FootboardMoveNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}

void FootboardMoveNode::moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint)
{
    static const float moveSpeed = 50.0f;
    
    this->stopAllActions();
    float duration = (startPoint - endPoint).length() / moveSpeed / 2.0f;
    this->setPosition(startPoint);
    auto moveTo1 = MoveTo::create(duration, endPoint);
    auto moveTo2 = MoveTo::create(duration, startPoint);
    this->runAction(Repeat::create(Sequence::create(moveTo1, moveTo2, nullptr), pow(2,30)));
}
