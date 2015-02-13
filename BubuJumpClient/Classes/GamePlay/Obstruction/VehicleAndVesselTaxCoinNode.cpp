#include "VehicleAndVesselTaxCoinNode.h"

USING_NS_CC;

VehicleAndVesselTaxCoinNode::~VehicleAndVesselTaxCoinNode()
{

}

bool VehicleAndVesselTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("VehicleAndVesselTaxCoinNode.csb", "VehicleAndVesselTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
