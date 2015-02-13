#include "DeedTaxCoinNode.h"

USING_NS_CC;

DeedTaxCoinNode::~DeedTaxCoinNode()
{

}

bool DeedTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("DeedTaxCoinNode.csb", "DeedTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
