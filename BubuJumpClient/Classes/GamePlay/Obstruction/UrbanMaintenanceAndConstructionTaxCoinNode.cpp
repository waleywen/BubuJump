#include "UrbanMaintenanceAndConstructionTaxCoinNode.h"

USING_NS_CC;

UrbanMaintenanceAndConstructionTaxCoinNode::~UrbanMaintenanceAndConstructionTaxCoinNode()
{

}

bool UrbanMaintenanceAndConstructionTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("UrbanMaintenanceAndConstructionTaxCoinNode.csb", "UrbanMaintenanceAndConstructionTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
