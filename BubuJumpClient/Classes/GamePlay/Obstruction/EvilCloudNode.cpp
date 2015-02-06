#include "EvilCloudNode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

EvilCloudNode::~EvilCloudNode()
{

}

bool EvilCloudNode::init()
{
    if (false == ObstructionNode::initWithCsbName("EvilCloudNode.csb"))
    {
        return false;
    }
    
    return true;
}

void EvilCloudNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(EvilCloudEffectType);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    this->setVisible(false);
}

void EvilCloudNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
