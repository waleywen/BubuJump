#ifndef _EvilCloudNode_H_
#define _EvilCloudNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class EvilCloudNode : public ObstructionNode
{
public:
    EvilCloudNode() : ObstructionNode(EvilCloudNodeType) {};
    virtual ~EvilCloudNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(EvilCloudNode);
};

#endif // _EvilCloudNode_H_
