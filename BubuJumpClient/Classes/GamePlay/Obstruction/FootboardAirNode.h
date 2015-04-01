#ifndef _FootboardAirNode_H_
#define _FootboardAirNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class FootboardAirNode : public ObstructionNode
{
public:
    FootboardAirNode() : ObstructionNode(FootboardAirNodeType) {};
    virtual ~FootboardAirNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(FootboardAirNode);
};

#endif // _FootboardAirNode_H_
