#include "TaxCoinNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

TaxCoinNode::~TaxCoinNode()
{
    if (nullptr != this->_tipsSpriteNode)
    {
        this->_tipsSpriteNode->release();
        this->_tipsSpriteNode = nullptr;
    }
}

bool TaxCoinNode::initWithCsbNameAndTipsName(const std::string& csbName, const std::string& tipsName)
{
    if (false == ObstructionNode::initWithCsbName(csbName))
    {
        return false;
    }
    
    this->_tipsSpriteNode = Sprite::create(tipsName);
    this->_tipsSpriteNode->retain();
    this->addChild(_tipsSpriteNode);
    
    return true;
}

void TaxCoinNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->addCoins(100);
    
    this->_mainSpriteNode->setVisible(false);
    this->_tipsSpriteNode->setVisible(true);
    
    this->_tipsSpriteNode->setScale(1.0f);
    auto delayTime = DelayTime::create(0.5f);
    auto scaleTo = ScaleTo::create(3.0f, 0.0f);
    auto sequence = Sequence::create(delayTime, scaleTo, NULL);
    this->_tipsSpriteNode->runAction(sequence);
    

    SimpleAudioEngine::getInstance()->playEffect("Sound/sfx-coin-pickup.wav");
}

void TaxCoinNode::reactivate()
{
    this->_mainSpriteNode->setVisible(true);
    this->_tipsSpriteNode->setVisible(false);

    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
