#ifndef _UFONode_H_
#define _UFONode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class UFONode : public ObstructionNode
{
public:
    UFONode() : ObstructionNode(UFONodeType) {};
    virtual ~UFONode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    void moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);
    
    CREATE_FUNC(UFONode);
};

#endif // _UFONode_H_
