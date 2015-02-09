#include "BuildingTaxCoinNode.h"

USING_NS_CC;

BuildingTaxCoinNode::~BuildingTaxCoinNode()
{

}

bool BuildingTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("BuildingTaxCoinNode.csb", "1.png"))
    {
        return false;
    }
    
    return true;
}
