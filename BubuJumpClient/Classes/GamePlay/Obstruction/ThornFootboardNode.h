#ifndef _ThornFootboardNode_H_
#define _ThornFootboardNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class ThornFootboardNode : public ObstructionNode
{
public:
    ThornFootboardNode() : ObstructionNode(ThornFootboardNodeType) {};
    virtual ~ThornFootboardNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(ThornFootboardNode);
};

#endif // _ThornFootboardNode_H_
