#include "BusinessIncomeTaxCoinNode.h"

USING_NS_CC;

BusinessIncomeTaxCoinNode::~BusinessIncomeTaxCoinNode()
{

}

bool BusinessIncomeTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("BusinessIncomeTaxCoinNode.csb", "1.png"))
    {
        return false;
    }
    
    return true;
}
