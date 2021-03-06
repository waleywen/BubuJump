#include "CharacterNode.h"

#include "Obstruction/Effect/BaseEffect.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocostudio::timeline;

CharacterNode::~CharacterNode()
{
    if (nullptr != this->_characterSpriteNode)
    {
        this->_characterSpriteNode->release();
        this->_characterSpriteNode = nullptr;
    }
    if (nullptr != this->_actionTimeline)
    {
        this->_actionTimeline->release();
        this->_actionTimeline = nullptr;
    }
}

bool CharacterNode::init()
{
    if (false == GameBaseNode::init())
    {
        return false;
    }
    
    this->_heartCount = 3;
    
    this->_characterSpriteNode = CSLoader::createNode("CharacterNode.csb");
    this->_characterSpriteNode->retain();
    this->_actionTimeline = CSLoader::createTimeline("CharacterNode.csb");
    this->_actionTimeline->retain();
    
    this->_characterSpriteNode->runAction(this->_actionTimeline);
    this->playIdleAnimation();
        
    this->addChild(this->_characterSpriteNode);
    
    //Test Code//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
//    this->schedule(schedule_selector(CharacterNode::testAnimation), 3.0f, kRepeatForever, 0);
    
    EffectFactory::getInstance()->getEffect(FlyBootEffectType);
    EffectFactory::getInstance()->getEffect(RocketEffectType);
    EffectFactory::getInstance()->getEffect(MagnetEffectType);
    EffectFactory::getInstance()->getEffect(AngelWingEffectType);
    EffectFactory::getInstance()->getEffect(EvilCloudEffectType);
    EffectFactory::getInstance()->getEffect(VortexEffectType);

    this->_characterSpriteNode->setScale(1.3f);
    
//    auto _rocketEffectSprite = Sprite::create("RocketEffect.png");
//    _rocketEffectSprite->retain();
//    this->addChild(_rocketEffectSprite, -10);
//    _rocketEffectSprite->setPosition(Vec2(0.0f, -200.0f));
//    auto sequenceAction = Sequence::create(RotateTo::create(2, 180), RotateTo::create(2, 360), NULL);
//    _rocketEffectSprite->runAction(Repeat::create(sequenceAction, pow(2,30)));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}

void CharacterNode::gameUpdate(float delta)
{
    if (this->getMode() == Waiting)
    {
        float percentage = this->getHorizontalSpeedPercentage();
        if (percentage > 0.015f || percentage < -0.015f)
        {
            if (percentage > 0.0f)
            {
                this->setScaleX(-1.0f);
            }
            else
            {
                this->setScaleX(1.0f);
            }
            float newX = this->getPosition().x + this->getHorizontalSpeedPercentage() * this->getMaxHorizontalSpeed();
            if (newX > this->getHorizontalMovingRange().end)
            {
                newX = this->getHorizontalMovingRange().end;
            }
            else if (newX < this->getHorizontalMovingRange().start)
            {
                newX = this->getHorizontalMovingRange().start;
            }
            this->setPosition(Vec2(newX, this->getPosition().y));
            
            if (this->getActionState() != Running)
            {
                this->playRunAnimation();
                this->setActionState(Running);
            }
        }
        else
        {
            if (this->getActionState() != Idling)
            {
                this->playIdleAnimation();
                this->setActionState(Idling);
            }
        }
    }
    else if (this->getMode() == Playing)
    {
        bool isFrozen = false;
        if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
        {
            this->getEffect()->gameUpdate(delta);
            isFrozen = this->getEffect()->isFrozen();
        }

        if (this->_hurtDuration > 0.0f)
        {
            this->_hurtDuration -= delta;
            if ((this->_hurtDuration - (int)this->_hurtDuration) <= 0.25f
                || ((this->_hurtDuration - (int)this->_hurtDuration) > 0.5f && (this->_hurtDuration - (int)this->_hurtDuration) <= 0.75))
            {
                this->_characterSpriteNode->setVisible(true);
            }
            else
            {
                this->_characterSpriteNode->setVisible(false);
            }
        }
        else
        {
            this->_characterSpriteNode->setVisible(true);
        }

        if (false == isFrozen)
        {
            float newXOffset = this->getHorizontalSpeedPercentage() * this->getMaxHorizontalSpeed();
            float newYOffset = this->getCurrentSpeed() * delta + (this->getCurrentAcceleration() * delta * delta) / 2;
            
            this->_currentSpeed = this->getCurrentSpeed() + this->getCurrentAcceleration() * delta;
            
            auto currentPosition = this->getPosition();
            float newX = currentPosition.x + newXOffset;
            float newY = currentPosition.y + newYOffset;
            
            if (newX > this->getHorizontalMovingRange().end)
            {
                newX = this->getHorizontalMovingRange().end;
            }
            else if (newX < this->getHorizontalMovingRange().start)
            {
                newX = this->getHorizontalMovingRange().start;
            }
            
            this->setPosition(Vec2(newX, newY));
            
            if (this->getCurrentSpeed() > 0.0f)
            {
                if (this->getActionState() != Jumping)
                {
                    this->setActionState(Jumping);
                    this->playJumpAnimation();
                }
            }
            else
            {
                if (this->getActionState() != Downing)
                {
                    this->setActionState(Downing);
                    this->playDownAnimation();
                }
            }
            
            for(auto& obstructionNode : *this->getObstructionNodeVector())
            {
                if ((ActivatedNodeState == obstructionNode->getState()) && this->isCollidedWithNode(*obstructionNode))
                {
                    obstructionNode->collided(this);
                }
            }
        }
    }
    else if (this->getMode() == Dead)
    {
        if (this->getCurrentSpeed() > 0.0f)
        {
            this->setCurrentSpeed(0.0f);
        }

        float newYOffset = this->getCurrentSpeed() * delta + (this->getCurrentAcceleration() * delta * delta) / 2;
        
        this->_currentSpeed = this->getCurrentSpeed() + this->getCurrentAcceleration() * delta;
        
        auto currentPosition = this->getPosition();
        float newY = currentPosition.y + newYOffset;
        
        this->setPosition(Vec2(this->getPosition().x, newY));
        
        if (this->getActionState() != Downing)
        {
            this->setActionState(Downing);
            this->playDownAnimation();
        }
        
        this->_characterSpriteNode->setVisible(true);
    }
}

void CharacterNode::startPlay()
{
    this->setMode(Playing);
    this->setScaleX(1.0f);
    this->setCurrentSpeed(this->getMaxVerticalSpeed());
    this->setActionState(Jumping);
    this->playJumpAnimation();
}

void CharacterNode::revive()
{
    this->setMode(Playing);
    this->_heartCount = 3;
    BaseEffect* effect = EffectFactory::getInstance()->getEffect(RocketEffectType);
    effect->setCharacterNode(this);
    this->setEffect(effect);
    this->setCurrentSpeed(0.0f);
}

void CharacterNode::goJump()
{
    if (false == this->_jumped && this->getMode() != Dead)
    {
        this->setCurrentSpeed(this->getMaxVerticalSpeed(), true);
    }
}

void CharacterNode::addHeart(int count)
{
    this->_heartCount += count;
    if (this->_heartCount > 3)
    {
        this->_heartCount = 3;
    }
}

void CharacterNode::dropHeart(int count)
{
    if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
    {
        if (this->getEffect()->getType() == RocketEffectType)
        {
            return;
        }
    }
    this->_heartCount -= count;
    
    if (this->_heartCount <= 0)
    {
        this->setMode(Dead);
        if (nullptr != this->getEffect())
        {
            this->_effect->reset();
            this->_effect->setState(InactivatedEffectState);
        }
        if (this->getCurrentSpeed() > 0.0f)
        {
            this->setCurrentSpeed(0.0f);
        }
        
        this->_heartCount = 0;
    }
    else
    {
        this->_hurtDuration = 2.0f;
    }
}

int CharacterNode::getHeartCount()
{
    return this->_heartCount;
}

void CharacterNode::addCoins(int coinCount, ObstructionNodeType type)
{
    if (SmallCoinNodeType != type
        && InvisibleCoinNodeType != type
        && SmallCoinMoveNodeType != type)
    {
        TaxCoinMapIterator iter = this->_taxCoinMap.find(type);
        if (this->_taxCoinMap.end() == iter)
        {
            this->_taxCoinMap.insert(TaxCoinPair(type, coinCount));
        }
        else
        {
            (*iter).second += coinCount;
        }
    }
    
    this->_coinAmount += coinCount;
}

void CharacterNode::dropCoins(int coinCount)
{
    this->_coinAmount = (coinCount >= this->_coinAmount ? 0.0f : (this->_coinAmount - coinCount));
}

int CharacterNode::getCoinAmount()
{
    return this->_coinAmount;
}

int CharacterNode::getTaxCoinAmount()
{
    int amount = 0;
    for (TaxCoinPair taxCoinPair : this->getTaxCoinMap())
    {
        amount += taxCoinPair.second;
    }
    return amount;
}

void CharacterNode::setEffect(BaseEffect *effect)
{
    if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
    {
        if (this->getEffect()->getGrade() > effect->getGrade())
        {
            return;
        }
    }
    
    if (nullptr != this->_effect)
    {
        this->_effect->reset();
    }
    this->_effect = effect;
}

BaseEffect* CharacterNode::getEffect()
{
    return this->_effect;
}

float CharacterNode::getCurrentSpeed()
{
    return this->_currentSpeed;
}

void CharacterNode::setCurrentSpeed(float currentSpeed, bool jumped)
{
    if (this->getMode() == Dead)
    {
        this->_currentSpeed = 0;
    }
    else
    {
        if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
        {
            currentSpeed = this->_effect->changeSpeed(currentSpeed);
        }
        this->_currentSpeed = currentSpeed;
        this->_jumped = jumped;
    }
}

void CharacterNode::setHorizontalSpeedPercentage(float percentage)
{
    this->_horizontalSpeedPercentage = percentage;
}

float CharacterNode::getHorizontalSpeedPercentage()
{
    if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
    {
        return this->_effect->changeHorizontalSpeedPercentage(this->_horizontalSpeedPercentage);
    }
    else
    {
        return this->_horizontalSpeedPercentage;
    }
}

float CharacterNode::getCurrentAcceleration()
{
    if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
    {
        return this->_effect->changeAcceleration(this->getNormalAcceleration());
    }
    else
    {
        return this->getNormalAcceleration();
    }
}

void CharacterNode::playIdleAnimation()
{
    this->_actionTimeline->gotoFrameAndPlay(10, 10, false);
}

void CharacterNode::playRunAnimation()
{
    this->_actionTimeline->gotoFrameAndPlay(50, 70, true);
}

void CharacterNode::playJumpAnimation()
{
    this->_actionTimeline->gotoFrameAndPlay(0, 20, false);
}

void CharacterNode::playDownAnimation()
{
    this->_actionTimeline->gotoFrameAndPlay(25, 45, false);
}

void CharacterNode::testAnimation(float t)
{
    this->playJumpAnimation();
}
