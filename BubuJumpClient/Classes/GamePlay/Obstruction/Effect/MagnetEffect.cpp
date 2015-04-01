#include "MagnetEffect.h"

#include "../../CharacterNode.h"
#include "../ObstructionNode.h"

USING_NS_CC;

MagnetEffect::~MagnetEffect()
{
}

bool MagnetEffect::init()
{
    if (false == SpriteBaseEffect::initWithSpriteName("MagnetEffect.png"))
    {
        return false;
    }
    
    this->_time = 5.0f;
    
    return true;
}

void MagnetEffect::gameUpdate(float delta)
{
    if (this->_duration == 0.0f)
    {
        this->_effectSprite->stopAllActions();
        auto sequenceAction = Sequence::create(RotateTo::create(2, 180), RotateTo::create(2, 360), NULL);
        this->_effectSprite->runAction(Repeat::create(sequenceAction, pow(2,30)));
    }
    
    if (nullptr == this->_effectSprite->getParent())
    {
        this->_effectSprite->setPosition(Vec2(0.0f, 0.0f));
        this->getCharacterNode()->addChild(this->_effectSprite, -10);
    }
    this->_effectSprite->setVisible(true);
    
    for(auto& obstructionNode : *this->getCharacterNode()->getObstructionNodeVector())
    {
        if ((obstructionNode->getNodeType() == SmallCoinNodeType
             || obstructionNode->getNodeType() == InvisibleCoinNodeType
             || obstructionNode->getNodeType() == IndividualIncomeTaxCoinNodeType
             || obstructionNode->getNodeType() == UrbanMaintenanceAndConstructionTaxCoinNodeType
             || obstructionNode->getNodeType() == BusinessTaxCoinNodeType
             || obstructionNode->getNodeType() == BusinessIncomeTaxCoinNodeType
             || obstructionNode->getNodeType() == BuildingTaxCoinNodeType
             || obstructionNode->getNodeType() == VehicleAndVesselTaxCoinNodeType
             || obstructionNode->getNodeType() == DeedTaxCoinNodeType
             || obstructionNode->getNodeType() == StampTaxCoinNodeType
             || obstructionNode->getNodeType() == LandValueIncrementTaxCoinNodeType
             || obstructionNode->getNodeType() == UrbanLandUseTaxCoinNodeType
             )
            && ActivatedNodeState == obstructionNode->getState())
        {
            Point obstructionNodePosition = obstructionNode->getPosition();
            Point characterNodePosition = this->getCharacterNode()->getPosition();
            if (characterNodePosition.getDistance(obstructionNodePosition) <= 500.0f)
            {
                static const float movingSpeed = 1600.0f;
                Point newPosition = obstructionNodePosition - ((obstructionNodePosition - characterNodePosition) * (delta * movingSpeed / (obstructionNodePosition - characterNodePosition).length()));
                obstructionNode->setPosition(newPosition);
            }
        }
    }
    
    this->setDuration(this->getDuration() + delta);
    if (ActivatedEffectState == this->getState() && this->getDuration() >= this->getTime())
    {
        this->setState(InactivatedEffectState);
        this->_effectSprite->setVisible(false);
    }
}

void MagnetEffect::reset()
{
    this->setState(ActivatedEffectState);
    this->setDuration(0.0f);
    this->_effectSprite->setVisible(false);
}
