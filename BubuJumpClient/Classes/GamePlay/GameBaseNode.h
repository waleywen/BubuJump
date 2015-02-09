#ifndef _GameBaseNode_H_
#define _GameBaseNode_H_

#include "cocos2d.h"

class GameBaseNode : public cocos2d::Node
{
public:
    GameBaseNode() : _collisionSize(), _collisionOffset(), _collisionColorLayer(nullptr) {};
    virtual ~GameBaseNode() = 0;
    
    virtual bool init() override;
    virtual void gameUpdate(float delta);
    cocos2d::Rect getCollisionRect() const;
    bool isCollidedWithNode(const GameBaseNode& gameBaseNode) const;
    
    //CREATE_FUNC(GameBaseNode);
    
    CC_PROPERTY(cocos2d::Size, _collisionSize, CollisionSize);
    CC_PROPERTY(cocos2d::Vec2, _collisionOffset, CollisionOffset);
private:
    void updateCollisionArea();
    
    cocos2d::LayerColor* _collisionColorLayer;
};

#endif // _GameBaseNode_H_
