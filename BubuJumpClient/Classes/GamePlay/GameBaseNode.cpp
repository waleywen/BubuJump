#include "GameBaseNode.h"

USING_NS_CC;

//#define ShowsCollisionArea

GameBaseNode::~GameBaseNode()
{
    if (nullptr != this->_collisionColorLayer)
    {
        this->_collisionColorLayer->release();
        this->_collisionColorLayer = nullptr;
    }
}

bool GameBaseNode::init()
{
    if (false == Node::init())
    {
        return false;
    }
    
#ifdef ShowsCollisionArea
    this->_collisionColorLayer = LayerColor::create(Color4B(255, 0, 0, 168));
    this->_collisionColorLayer->retain();
    this->_collisionColorLayer->setContentSize(Size(0.0f, 0.0f));
    this->addChild(this->_collisionColorLayer, 100);
#endif
    
    return true;
}

void GameBaseNode::gameUpdate(float delta)
{
    
}

Rect GameBaseNode::getCollisionRect() const
{
    Rect collisionRect;
    collisionRect.origin = this->getPosition() + this->_collisionOffset - this->_collisionSize / 2.0f;
    collisionRect.size = this->_collisionSize;
    return collisionRect;
}

bool GameBaseNode::isCollidedWithNode(const GameBaseNode &gameBaseNode) const
{
    return this->getCollisionRect().intersectsRect(gameBaseNode.getCollisionRect());
}

void GameBaseNode::setCollisionSize(cocos2d::Size contentSize)
{
    this->_collisionSize = contentSize;
    
    this->updateCollisionArea();
}

Size GameBaseNode::getCollisionSize()
{
    return this->_collisionSize;
}

void GameBaseNode::setCollisionOffset(cocos2d::Vec2 collisionOffset)
{
    this->_collisionOffset = collisionOffset;
    
    this->updateCollisionArea();
}

Vec2 GameBaseNode::getCollisionOffset()
{
    return this->_collisionOffset;
}

void GameBaseNode::updateCollisionArea()
{
#ifdef ShowsCollisionArea
    this->_collisionColorLayer->setContentSize(this->_collisionSize);
    auto newPosition = this->_collisionOffset - this->_collisionSize / 2.0f;
    this->_collisionColorLayer->setPosition(newPosition);
#endif
}
