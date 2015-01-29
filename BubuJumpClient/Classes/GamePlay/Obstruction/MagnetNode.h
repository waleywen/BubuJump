#ifndef _MagnetNode_H_
#define _MagnetNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class MagnetNode : public ObstructionNode
{
public:
    MagnetNode() : ObstructionNode(MagnetNodeType) {};
    virtual ~MagnetNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(MagnetNode);
};

#endif // MagnetNode
