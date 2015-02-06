#ifndef _VortexNode_H_
#define _VortexNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class VortexNode : public ObstructionNode
{
public:
    VortexNode() : ObstructionNode(VortexNodeType) {};
    virtual ~VortexNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(VortexNode);
};

#endif // _VortexNode_H_
