#include "InvisibleCoinNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

InvisibleCoinNode::~InvisibleCoinNode()
{
    if (nullptr != this->_tipsSpriteNode)
    {
        this->_tipsSpriteNode->release();
        this->_tipsSpriteNode = nullptr;
    }
}

bool InvisibleCoinNode::init()
{
    if (false == ObstructionNode::initWithCsbName("InvisibleCoinNode.csb"))
    {
        return false;
    }
    
    this->_tipsSpriteNode = Sprite::create("InvisibleAddTips.png");
    this->_tipsSpriteNode->retain();
    this->addChild(_tipsSpriteNode);

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
    characterNode->addCoins(100, this->getNodeType());
    this->_mainSpriteNode->setVisible(false);

    this->_tipsSpriteNode->setVisible(true);
    this->_tipsSpriteNode->setScale(1.0f);
    auto delayTime = DelayTime::create(0.5f);
    auto scaleTo = ScaleTo::create(3.0f, 0.0f);
    auto sequence = Sequence::create(delayTime, scaleTo, NULL);
    this->_tipsSpriteNode->runAction(sequence);

    SimpleAudioEngine::getInstance()->playEffect("Sound/sfx-coin-pickup.wav");
}

void InvisibleCoinNode::reactivate()
{
    this->_mainSpriteNode->setVisible(true);
    this->_tipsSpriteNode->setVisible(false);

    this->setState(ActivatedNodeState);
    this->setVisible(false);
}
