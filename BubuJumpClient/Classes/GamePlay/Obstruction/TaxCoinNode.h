#ifndef _TaxCoinNode_H_
#define _TaxCoinNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class TaxCoinNode : public ObstructionNode
{
public:
    TaxCoinNode(ObstructionNodeType nodeType) : ObstructionNode(nodeType), _tipsSpriteNode(nullptr) {};
    virtual ~TaxCoinNode();
    
    bool initWithCsbNameAndTipsName(const std::string& csbName, const std::string& tipsName);
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

protected:
    cocos2d::Node* _tipsSpriteNode;
};

#endif // _TaxCoinNode_H_
