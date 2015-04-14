#ifndef _ThornFootboardMoveNode_H_
#define _ThornFootboardMoveNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class ThornFootboardMoveNode : public ObstructionNode
{
public:
    ThornFootboardMoveNode() : ObstructionNode(ThornFootboardMoveNodeType) {};
    virtual ~ThornFootboardMoveNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    void moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);

    CREATE_FUNC(ThornFootboardMoveNode);
};

#endif // _ThornFootboardMoveNode_H_
