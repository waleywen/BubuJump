#ifndef _BusinessTaxCoinNode_H_
#define _BusinessTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class BusinessTaxCoinNode : public TaxCoinNode
{
public:
    BusinessTaxCoinNode() : TaxCoinNode(BusinessTaxCoinNodeType) {};
    virtual ~BusinessTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(BusinessTaxCoinNode);
};

#endif // _BusinessTaxCoinNode_H_
