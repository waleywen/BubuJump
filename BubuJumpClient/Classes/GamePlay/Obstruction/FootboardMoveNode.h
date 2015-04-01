#ifndef _FootboardMoveNode_H_
#define _FootboardMoveNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class FootboardMoveNode : public ObstructionNode
{
public:
    FootboardMoveNode() : ObstructionNode(FootboardMoveNodeType) {};
    virtual ~FootboardMoveNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    void moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);

    CREATE_FUNC(FootboardMoveNode);
};

#endif // _FootboardMoveNode_H_
