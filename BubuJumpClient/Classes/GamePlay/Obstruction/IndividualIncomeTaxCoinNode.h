#ifndef _IndividualIncomeTaxCoinNode_H_
#define _IndividualIncomeTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class IndividualIncomeTaxCoinNode : public TaxCoinNode
{
public:
    IndividualIncomeTaxCoinNode() : TaxCoinNode(IndividualIncomeTaxCoinNodeType) {};
    virtual ~IndividualIncomeTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(IndividualIncomeTaxCoinNode);
};

#endif // _IndividualIncomeTaxCoinNode_H_
