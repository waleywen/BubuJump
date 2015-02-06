#include "ThornFootboardNode.h"

#include "../CharacterNode.h"

USING_NS_CC;

ThornFootboardNode::~ThornFootboardNode()
{

}

bool ThornFootboardNode::init()
{
    if (false == ObstructionNode::initWithCsbName("ThornFootboardNode.csb"))
    {
        return false;
    }
    
    return true;
}

void ThornFootboardNode::collided(CharacterNode *characterNode)
{
    if (Downing == characterNode->getActionState())
    {
        float v = characterNode->getCurrentSpeed();
        float a = -1000;
        float distance = -(v * v / 2.0f / a);
        if (characterNode->getPosition().y + distance - this->getPosition().y > (this->getCollisionSize().height + characterNode->getCollisionSize().height) / 2.0f)
        {
            characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
            characterNode->dropHeart(1);
        }
    }
}

void ThornFootboardNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
