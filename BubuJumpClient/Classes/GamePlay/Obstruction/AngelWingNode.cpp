#include "AngelWingNode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

AngelWingNode::~AngelWingNode()
{

}

bool AngelWingNode::init()
{
    if (false == ObstructionNode::initWithCsbName("AngelWingNode.csb"))
    {
        return false;
    }
    
    return true;
}

void AngelWingNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(AngelWingEffectType);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    this->setVisible(false);
}

void AngelWingNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
