#ifndef _SoftCloudNode_H_
#define _SoftCloudNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class SoftCloudNode : public ObstructionNode
{
public:
    SoftCloudNode() : ObstructionNode(SoftCloudNodeType) {};
    virtual ~SoftCloudNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(SoftCloudNode);
};

#endif // _SoftCloudNode_H_
