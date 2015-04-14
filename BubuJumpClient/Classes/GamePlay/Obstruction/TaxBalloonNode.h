#ifndef _TaxBalloonNode_H_
#define _TaxBalloonNode_H_

#include "cocos2d.h"

#include "ObstructionNode.h"

class TaxBalloonNode : public ObstructionNode
{
public:
    TaxBalloonNode() : ObstructionNode(TaxBalloonNodeType), _tipsSpriteNode(nullptr) {};
    virtual ~TaxBalloonNode();
    
    virtual bool init() override;
    virtual void collided(CharacterNode* characterNode) override;
    virtual void reactivate() override;

    void moveWithRange(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);

    CREATE_FUNC(TaxBalloonNode);
private:
    cocos2d::Node* _tipsSpriteNode;
};

#endif // _TaxBalloonNode_H_
