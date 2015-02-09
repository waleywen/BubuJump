#ifndef _VehicleAndVesselTaxCoinNode_H_
#define _VehicleAndVesselTaxCoinNode_H_

#include "cocos2d.h"

#include "TaxCoinNode.h"

class VehicleAndVesselTaxCoinNode : public TaxCoinNode
{
public:
    VehicleAndVesselTaxCoinNode() : TaxCoinNode(VehicleAndVesselTaxCoinNodeType) {};
    virtual ~VehicleAndVesselTaxCoinNode();
    
    virtual bool init() override;

    CREATE_FUNC(VehicleAndVesselTaxCoinNode);
};

#endif // _VehicleAndVesselTaxCoinNode_H_
