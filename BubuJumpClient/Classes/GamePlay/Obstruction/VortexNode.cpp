#include "VortexNode.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;

VortexNode::~VortexNode()
{

}

bool VortexNode::init()
{
    if (false == ObstructionNode::initWithCsbName("VortexNode.csb"))
    {
        return false;
    }
    
    auto actionTimeline = CSLoader::createTimeline("VortexNode.csb");
    this->_mainSpriteNode->runAction(actionTimeline);
    actionTimeline->gotoFrameAndPlay(0, true);

    return true;
}

void VortexNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(VortexEffectType, this);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
}

void VortexNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
