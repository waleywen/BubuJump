#include "BuildingTaxCoinNode.h"

USING_NS_CC;

BuildingTaxCoinNode::~BuildingTaxCoinNode()
{

}

bool BuildingTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("BuildingTaxCoinNode.csb", "BuildingTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
