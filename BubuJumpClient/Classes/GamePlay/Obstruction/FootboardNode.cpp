#include "FootboardNode.h"

#include "../CharacterNode.h"

USING_NS_CC;

FootboardNode::~FootboardNode()
{

}

bool FootboardNode::init()
{
    if (false == ObstructionNode::initWithCsbName("FootboardNode.csb"))
    {
        return false;
    }
    
    return true;
}

void FootboardNode::collided(CharacterNode *characterNode)
{
    if (Downing == characterNode->getActionState())
    {
        float v = characterNode->getCurrentSpeed();
        float a = -1000;
        float distance = -(v * v / 2.0f / a);
        if (characterNode->getPosition().y + distance - this->getPosition().y > (this->getCollisionSize().height + characterNode->getCollisionSize().height) / 2.0f)
        {
            characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
        }
    }
}

void FootboardNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
