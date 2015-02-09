#include "UFONode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

UFONode::~UFONode()
{

}

bool UFONode::init()
{
    if (false == ObstructionNode::initWithCsbName("UFONode.csb"))
    {
        return false;
    }
    
    auto actionTimeline = CSLoader::createTimeline("UFONode.csb");
    this->_mainSpriteNode->runAction(actionTimeline);
    actionTimeline->gotoFrameAndPlay(0, true);

    return true;
}

void UFONode::collided(CharacterNode *characterNode)
{
    this->setState(InactivatedNodeState);
    characterNode->setCurrentSpeed(0.0f);
}

void UFONode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}

void UFONode::moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint)
{
    static const float moveSpeed = 100.0f;
    
    this->stopAllActions();
    float duration = (startPoint - endPoint).length() / moveSpeed / 2.0f;
    this->setPosition(startPoint);
    auto moveTo1 = MoveTo::create(duration, endPoint);
    auto moveTo2 = MoveTo::create(duration, startPoint);
    this->runAction(Sequence::create(moveTo1, moveTo2, nullptr));
}