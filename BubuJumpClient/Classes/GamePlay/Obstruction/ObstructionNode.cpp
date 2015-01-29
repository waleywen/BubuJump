#include "ObstructionNode.h"

#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocostudio::timeline;

ObstructionNode::~ObstructionNode()
{
    if (nullptr != this->_mainSpriteNode)
    {
        this->_mainSpriteNode->release();
        this->_mainSpriteNode = nullptr;
    }
}

bool ObstructionNode::initWithCsbName(const std::string& csbName)
{
    if (false == GameBaseNode::init())
    {
        return false;
    }
    
    this->_mainSpriteNode = CSLoader::createNode(csbName);
    this->_mainSpriteNode->retain();
    
    this->addChild(this->_mainSpriteNode);

    return true;
}
