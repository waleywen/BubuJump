#include "ThornFootboardNode.h"

#include "../../Audio/AudioManager.h"

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
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->dropHeart(1);
    this->setVisible(false);
    
    AudioManager::getInstance()->playEffect("Sound/sfx-thorn-footboard.aac");
}

void ThornFootboardNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
