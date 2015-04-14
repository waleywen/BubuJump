#ifndef _MeteoriteNode_H_
#define _MeteoriteNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class MeteoriteNode : public ObstructionNode
{
public:
    MeteoriteNode() : ObstructionNode(MeteoriteNodeType) {};
    virtual ~MeteoriteNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    void moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);

    CREATE_FUNC(MeteoriteNode);
};

#endif // _MeteoriteNode_H_
