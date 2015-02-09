#ifndef _BuildingTaxCoinNode_H_
#define _BuildingTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class BuildingTaxCoinNode : public TaxCoinNode
{
public:
    BuildingTaxCoinNode() : TaxCoinNode(BuildingTaxCoinNodeType) {};
    virtual ~BuildingTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(BuildingTaxCoinNode);
};

#endif // _BuildingTaxCoinNode_H_
