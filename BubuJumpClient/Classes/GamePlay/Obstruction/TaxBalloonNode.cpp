#include "TaxBalloonNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

TaxBalloonNode::~TaxBalloonNode()
{
    if (nullptr != this->_tipsSpriteNode)
    {
        this->_tipsSpriteNode->release();
        this->_tipsSpriteNode = nullptr;
    }
}

bool TaxBalloonNode::init()
{
    if (false == ObstructionNode::initWithCsbName("TaxBalloonNode.csb"))
    {
        return false;
    }
    
    this->_tipsSpriteNode = Sprite::create("TaxBalloonTips.png");
    this->_tipsSpriteNode->retain();
    this->addChild(_tipsSpriteNode);
    this->_tipsSpriteNode->setVisible(false);
    
    return true;
}

void TaxBalloonNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    characterNode->dropHeart(3);

    this->_mainSpriteNode->setVisible(false);
//    this->_tipsSpriteNode->setVisible(true);
//    
//    this->_tipsSpriteNode->setScale(1.0f);
//    auto delayTime = DelayTime::create(0.5f);
//    auto scaleTo = ScaleTo::create(3.0f, 0.0f);
//    auto sequence = Sequence::create(delayTime, scaleTo, NULL);
//    this->_tipsSpriteNode->runAction(sequence);

//    AudioManager::getInstance()->playEffect("Sound/sfx-coin-pickup.wav");
}

void TaxBalloonNode::reactivate()
{
    this->_mainSpriteNode->setVisible(true);
//    this->_tipsSpriteNode->setVisible(false);

    this->setState(ActivatedNodeState);
    this->setVisible(true);
}

void TaxBalloonNode::moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint)
{
    static const float moveSpeed = 50.0f;
    
    this->stopAllActions();
    float duration = (startPoint - endPoint).length() / moveSpeed / 2.0f;
    this->setPosition(startPoint);
    auto moveTo1 = MoveTo::create(duration, endPoint);
    auto moveTo2 = MoveTo::create(duration, startPoint);
    this->runAction(Repeat::create(Sequence::create(moveTo1, moveTo2, nullptr), pow(2,30)));
}
