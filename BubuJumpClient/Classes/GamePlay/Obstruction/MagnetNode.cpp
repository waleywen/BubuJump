#include "MagnetNode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

MagnetNode::~MagnetNode()
{

}

bool MagnetNode::init()
{
    if (false == ObstructionNode::initWithCsbName("MagnetNode.csb"))
    {
        return false;
    }
    
    return true;
}

void MagnetNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(MagnetEffectType);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    this->setVisible(false);
}

void MagnetNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
