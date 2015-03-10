#include "LandValueIncrementTaxCoinNode.h"

USING_NS_CC;

LandValueIncrementTaxCoinNode::~LandValueIncrementTaxCoinNode()
{

}

bool LandValueIncrementTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("LandValueIncrementTaxCoinNode.csb", "LandValueIncrementTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
