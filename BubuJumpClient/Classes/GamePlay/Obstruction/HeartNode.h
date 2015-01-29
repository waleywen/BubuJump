#ifndef _HeartNode_H_
#define _HeartNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class HeartNode : public ObstructionNode
{
public:
    HeartNode() : ObstructionNode(HeartNodeType) {};
    virtual ~HeartNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(HeartNode);
};

#endif // _HeartNode_H_
