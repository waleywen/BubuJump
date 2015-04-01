#ifndef _FootboardSpaceNode_H_
#define _FootboardSpaceNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class FootboardSpaceNode : public ObstructionNode
{
public:
    FootboardSpaceNode() : ObstructionNode(FootboardSpaceNodeType) {};
    virtual ~FootboardSpaceNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(FootboardSpaceNode);
};

#endif // _FootboardSpaceNode_H_
