#ifndef _SmallCoinMoveNode_H_
#define _SmallCoinMoveNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class SmallCoinMoveNode : public ObstructionNode
{
public:
    SmallCoinMoveNode() : ObstructionNode(SmallCoinMoveNodeType) {};
    virtual ~SmallCoinMoveNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    void moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);

    CREATE_FUNC(SmallCoinMoveNode);
};

#endif // _SmallCoinMoveNode_H_
