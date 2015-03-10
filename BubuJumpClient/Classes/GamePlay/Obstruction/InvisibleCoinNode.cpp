#include "InvisibleCoinNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

InvisibleCoinNode::~InvisibleCoinNode()
{

}

bool InvisibleCoinNode::init()
{
    if (false == ObstructionNode::initWithCsbName("InvisibleCoinNode.csb"))
    {
        return false;
    }
    
    return true;
}

void InvisibleCoinNode::gameUpdate(float delta)
{
    if (ActivatedNodeState == this->getState() && nullptr != this->getCharacterNode())
    {
        if ((this->getPosition() - this->getCharacterNode()->getPosition()).length() < 400.0f)
        {
            this->setVisible(true);
        }
    }
}

void InvisibleCoinNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->addCoins(10, this->getNodeType());
    this->setVisible(false);

    SimpleAudioEngine::getInstance()->playEffect("Sound/sfx-coin-pickup.wav");
}

void InvisibleCoinNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(false);
}
