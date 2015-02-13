#ifndef _StampTaxCoinNode_H_
#define _StampTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class StampTaxCoinNode : public TaxCoinNode
{
public:
    StampTaxCoinNode() : TaxCoinNode(StampTaxCoinNodeType) {};
    virtual ~StampTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(StampTaxCoinNode);
};

#endif // _StampTaxCoinNode_H_
