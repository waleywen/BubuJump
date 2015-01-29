#ifndef _ObstructionNode_H_
#define _ObstructionNode_H_

#include "cocos2d.h"

#include "../GameBaseNode.h"

class CharacterNode;

enum ObstructionNodeType
{
    NoneNodeType,
    SmallCoinNodeType,
    IndividualIncomeTaxCoinNodeType,
    UrbanMaintenanceAndConstructionTaxCoinNodeType,
    FootboardNodeType,
    HeartNodeType,
    FlyBootNodeType,
    RocketNodeType,
    MagnetNodeType,
};

enum ObstructionNodeState
{
    InactivatedNodeState,
    ActivatedNodeState,
    PendingNodeState,
};

class ObstructionNode : public GameBaseNode
{
public:
    ObstructionNode(ObstructionNodeType nodeType) : _nodeType(nodeType), _state(InactivatedNodeState), _mainSpriteNode(nullptr), _rootNode(nullptr) {};
    virtual ~ObstructionNode() = 0;
    
    bool initWithCsbName(const std::string& csbName);
    virtual void collided(CharacterNode* characterNode) = 0;
    virtual void reactivate() = 0;
    
    CC_SYNTHESIZE(ObstructionNodeType, _nodeType, NodeType);
    CC_SYNTHESIZE(ObstructionNodeState, _state, State);

    CC_SYNTHESIZE(cocos2d::Node*, _rootNode, RootNode);
protected:
    cocos2d::Node* _mainSpriteNode;
};

#endif // _ObstructionNode_H_
