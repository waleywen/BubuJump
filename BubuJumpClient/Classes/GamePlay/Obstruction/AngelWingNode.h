#ifndef _AngelWingNode_H_
#define _AngelWingNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class AngelWingNode : public ObstructionNode
{
public:
    AngelWingNode() : ObstructionNode(AngelWingNodeType) {};
    virtual ~AngelWingNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(AngelWingNode);
};

#endif // _AngelWingNode_H_
