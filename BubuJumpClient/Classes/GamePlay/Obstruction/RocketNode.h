#ifndef _RocketNode_H_
#define _RocketNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class RocketNode : public ObstructionNode
{
public:
    RocketNode() : ObstructionNode(RocketNodeType) {};
    virtual ~RocketNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(RocketNode);
};

#endif // _RocketNode_H_
