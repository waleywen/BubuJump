#ifndef _UrbanMaintenanceAndConstructionTaxCoinNode_H_
#define _UrbanMaintenanceAndConstructionTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class UrbanMaintenanceAndConstructionTaxCoinNode : public TaxCoinNode
{
public:
    UrbanMaintenanceAndConstructionTaxCoinNode() : TaxCoinNode(UrbanMaintenanceAndConstructionTaxCoinNodeType) {};
    virtual ~UrbanMaintenanceAndConstructionTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(UrbanMaintenanceAndConstructionTaxCoinNode);
};

#endif // _UrbanMaintenanceAndConstructionTaxCoinNode_H_
