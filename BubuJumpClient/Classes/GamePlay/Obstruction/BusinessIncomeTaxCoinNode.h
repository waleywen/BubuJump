#ifndef _BusinessIncomeTaxCoinNode_H_
#define _BusinessIncomeTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class BusinessIncomeTaxCoinNode : public TaxCoinNode
{
public:
    BusinessIncomeTaxCoinNode() : TaxCoinNode(BusinessIncomeTaxCoinNodeType) {};
    virtual ~BusinessIncomeTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(BusinessIncomeTaxCoinNode);
};

#endif // _BusinessIncomeTaxCoinNode_H_
