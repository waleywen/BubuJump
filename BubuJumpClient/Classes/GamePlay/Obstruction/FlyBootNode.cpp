#include "FlyBootNode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

FlyBootNode::~FlyBootNode()
{

}

bool FlyBootNode::init()
{
    if (false == ObstructionNode::initWithCsbName("FlyBootNode.csb"))
    {
        return false;
    }
    
    return true;
}

void FlyBootNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(FlyBootEffectType);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    this->setVisible(false);
}

void FlyBootNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
