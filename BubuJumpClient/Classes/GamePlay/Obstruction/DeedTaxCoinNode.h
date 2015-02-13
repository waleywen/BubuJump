#ifndef _DeedTaxCoinNode_H_
#define _DeedTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class DeedTaxCoinNode : public TaxCoinNode
{
public:
    DeedTaxCoinNode() : TaxCoinNode(DeedTaxCoinNodeType) {};
    virtual ~DeedTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(DeedTaxCoinNode);
};

#endif // _DeedTaxCoinNode_H_
