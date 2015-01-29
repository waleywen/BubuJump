#ifndef _FootboardNode_H_
#define _FootboardNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class FootboardNode : public ObstructionNode
{
public:
    FootboardNode() : ObstructionNode(FootboardNodeType) {};
    virtual ~FootboardNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(FootboardNode);
};

#endif // _FootboardNode_H_
