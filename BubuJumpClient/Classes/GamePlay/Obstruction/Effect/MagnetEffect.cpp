#include "MagnetEffect.h"

#include "../../CharacterNode.h"
#include "../ObstructionNode.h"

USING_NS_CC;

MagnetEffect::~MagnetEffect()
{
    if (nullptr != this->_magnetEffectSprite)
    {
        this->_magnetEffectSprite->release();
        this->_magnetEffectSprite = nullptr;
    }
}

bool MagnetEffect::init()
{
    if (false == BaseEffect::init())
    {
        return false;
    }
    
    this->_time = 10.0f;
    
    this->_magnetEffectSprite = Sprite::create("MagnetEffect.png");
    this->_magnetEffectSprite->retain();
    auto sequenceAction = Sequence::create(RotateTo::create(2, 180), RotateTo::create(2, 360), NULL);
    _magnetEffectSprite->runAction(Repeat::create(sequenceAction, pow(2,30)));

    return true;
}

void MagnetEffect::gameUpdate(float delta)
{
    if (nullptr == this->_magnetEffectSprite->getParent())
    {
        this->_magnetEffectSprite->setPosition(Vec2(0.0f, 0.0f));
        this->getCharacterNode()->addChild(this->_magnetEffectSprite, -10);
    }
    this->_magnetEffectSprite->setVisible(true);
    this->setDuration(this->getDuration() + delta);
    
    for(auto& obstructionNode : *this->getCharacterNode()->getObstructionNodeVector())
    {
        if ((obstructionNode->getNodeType() == SmallCoinNodeType
            || obstructionNode->getNodeType() == IndividualIncomeTaxCoinNodeType
            || obstructionNode->getNodeType() == UrbanMaintenanceAndConstructionTaxCoinNodeType)
            && ActivatedNodeState == obstructionNode->getState())
        {
            Point obstructionNodePosition = obstructionNode->getPosition();
            Point characterNodePosition = this->getCharacterNode()->getPosition();
            if (characterNodePosition.getDistance(obstructionNodePosition) <= 500.0f)
            {
                const float moveSpeed = 1000.0f;
                Point newPosition = obstructionNodePosition - ((obstructionNodePosition - characterNodePosition) * (delta * moveSpeed / (obstructionNodePosition - characterNodePosition).length()));
                obstructionNode->setPosition(newPosition);
            }
        }
    }
    
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_magnetEffectSprite->setVisible(false);
    }
}

void MagnetEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_magnetEffectSprite->setVisible(false);
}
