#include "SoftCloudNode.h"

#include "../CharacterNode.h"

USING_NS_CC;

SoftCloudNode::~SoftCloudNode()
{

}

bool SoftCloudNode::init()
{
    if (false == ObstructionNode::initWithCsbName("SoftCloudNode.csb"))
    {
        return false;
    }
    
    return true;
}

void SoftCloudNode::collided(CharacterNode *characterNode)
{
    if (Downing == characterNode->getActionState())
    {
        float v = characterNode->getCurrentSpeed();
        float a = -1000;
        float distance = -(v * v / 2.0f / a);
        if (characterNode->getPosition().y + distance - this->getPosition().y > (this->getCollisionSize().height + characterNode->getCollisionSize().height) / 2.0f)
        {
            characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
            this->setState(InactivatedNodeState);
            this->setVisible(false);
        }
    }
}

void SoftCloudNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
