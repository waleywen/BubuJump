#ifndef _UrbanLandUseTaxCoinNode_H_
#define _UrbanLandUseTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class UrbanLandUseTaxCoinNode : public TaxCoinNode
{
public:
    UrbanLandUseTaxCoinNode() : TaxCoinNode(UrbanLandUseTaxCoinNodeType) {};
    virtual ~UrbanLandUseTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(UrbanLandUseTaxCoinNode);
};

#endif // _UrbanLandUseTaxCoinNode_H_
