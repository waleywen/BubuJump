#include "HeartNode.h"

#include "../CharacterNode.h"

USING_NS_CC;

HeartNode::~HeartNode()
{

}

bool HeartNode::init()
{
    if (false == ObstructionNode::initWithCsbName("HeartNode.csb"))
    {
        return false;
    }
    
    return true;
}

void HeartNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->addHeart(1);
    this->setVisible(false);
}

void HeartNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
