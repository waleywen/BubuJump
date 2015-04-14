#include "ThornFootboardNode.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

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
    characterNode->dropHeart(3);
    this->setVisible(false);
    
    if (nullptr == characterNode->getEffect() || InactivatedEffectState == characterNode->getEffect()->getState() || RocketEffectType != characterNode->getEffect()->getType())
    {
        AudioManager::getInstance()->playEffect("Sound/sfx-thorn-footboard.aac");
    }
}

void ThornFootboardNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
