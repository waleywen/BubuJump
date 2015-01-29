#ifndef _SmallCoinNode_H_
#define _SmallCoinNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class SmallCoinNode : public ObstructionNode
{
public:
    SmallCoinNode() : ObstructionNode(SmallCoinNodeType) {};
    virtual ~SmallCoinNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(SmallCoinNode);
};

#endif // _SmallCoinNode_H_
