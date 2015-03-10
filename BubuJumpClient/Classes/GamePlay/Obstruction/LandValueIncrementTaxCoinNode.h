#ifndef _LandValueIncrementTaxCoinNode_H_
#define _LandValueIncrementTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class LandValueIncrementTaxCoinNode : public TaxCoinNode
{
public:
    LandValueIncrementTaxCoinNode() : TaxCoinNode(LandValueIncrementTaxCoinNodeType) {};
    virtual ~LandValueIncrementTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(LandValueIncrementTaxCoinNode);
};

#endif // _LandValueIncrementTaxCoinNode_H_
