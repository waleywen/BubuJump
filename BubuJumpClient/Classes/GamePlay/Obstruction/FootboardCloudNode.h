#ifndef _FootboardCloudNode_H_
#define _FootboardCloudNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class FootboardCloudNode : public ObstructionNode
{
public:
    FootboardCloudNode() : ObstructionNode(FootboardCloudNodeType) {};
    virtual ~FootboardCloudNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(FootboardCloudNode);
};

#endif // _FootboardCloudNode_H_
