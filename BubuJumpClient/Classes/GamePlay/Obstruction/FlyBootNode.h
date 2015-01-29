#ifndef _FlyBootNode_H_
#define _FlyBootNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class FlyBootNode : public ObstructionNode
{
public:
    FlyBootNode() : ObstructionNode(FlyBootNodeType) {};
    virtual ~FlyBootNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(FlyBootNode);
};

#endif // _FlyBootNode_H_
