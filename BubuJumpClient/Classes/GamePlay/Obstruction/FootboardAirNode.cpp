#include "FootboardAirNode.h"

#include "audio/include/SimpleAudioEngine.h"

#include "../../Audio/AudioManager.h"

#include "../CharacterNode.h"

USING_NS_CC;
using namespace CocosDenshion;

FootboardAirNode::~FootboardAirNode()
{

}

bool FootboardAirNode::init()
{
    if (false == ObstructionNode::initWithCsbName("FootboardAirNode.csb"))
    {
        return false;
    }
    
    return true;
}

void FootboardAirNode::collided(CharacterNode *characterNode)
{
    if (Downing == characterNode->getActionState())
    {
        float v = characterNode->getCurrentSpeed();
        float a = -1000;
        float distance = -(v * v / 2.0f / a);
        if (characterNode->getPosition().y + distance - this->getPosition().y > (this->getCollisionSize().height + characterNode->getCollisionSize().height) / 2.0f)
        {
            characterNode->setCurrentSpeed(characterNode->getMaxVerticalSpeed());
            
            AudioManager::getInstance()->playEffect("Sound/sfx-footboard.wav");
        }
    }
}

void FootboardAirNode::reactivate()
{
    this->setState(ActivatedNodeState);
    this->setVisible(true);
}
