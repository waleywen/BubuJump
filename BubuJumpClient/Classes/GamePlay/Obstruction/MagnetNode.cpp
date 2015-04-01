#include "MagnetNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"
#include "Effect/BaseEffect.h"

USING_NS_CC;
using namespace CocosDenshion;

MagnetNode::~MagnetNode()
{

}

bool MagnetNode::init()
{
    if (false == ObstructionNode::initWithCsbName("MagnetNode.csb"))
    {
        return false;
    }
    
    return true;
}

void MagnetNode::collided(CharacterNode *characterNode)
{
    this->setState(PendingNodeState);
    auto effect = EffectFactory::getInstance()->getEffect(MagnetEffectType);
    effect->setCharacterNode(characterNode);
    characterNode->setEffect(effect);
    characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
    this->setVisible(false);
    
    if (characterNode->getEffect()->getGrade() <= effect->getGrade())
    {
        AudioManager::getInstance()->playEffect("Sound/sfx-magnet.wav");
    }
}

void MagnetNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
