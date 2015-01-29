#include "SmallCoinNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

SmallCoinNode::~SmallCoinNode()
{

}

bool SmallCoinNode::init()
{
    if (false == ObstructionNode::initWithCsbName("SmallCoinNode.csb"))
    {
        return false;
    }
    
    return true;
}

void SmallCoinNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->addCoins(10);
    this->setVisible(false);

    SimpleAudioEngine::getInstance()->playEffect("Sound/sfx-coin-pickup.wav");
}

void SmallCoinNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
