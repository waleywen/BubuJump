#include "RocketNode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

RocketNode::~RocketNode()
{

}

bool RocketNode::init()
{
    if (false == ObstructionNode::initWithCsbName("RocketNode.csb"))
    {
        return false;
    }
    
    return true;
}

void RocketNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(RocketEffectType);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    this->setVisible(false);
}

void RocketNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
