#ifndef _InvisibleCoinNode_H_
#define _InvisibleCoinNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class InvisibleCoinNode : public ObstructionNode
{
public:
    InvisibleCoinNode() : ObstructionNode(InvisibleCoinNodeType), _characterNode(nullptr), _tipsSpriteNode(nullptr) {};
    virtual ~InvisibleCoinNode();
    
    virtual bool init() override;
    virtual void gameUpdate(float delta) override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    CREATE_FUNC(InvisibleCoinNode);

    CC_SYNTHESIZE(CharacterNode*, _characterNode, CharacterNode);
private:
    cocos2d::Node* _tipsSpriteNode;
};

#endif // _InvisibleCoinNode_H_
