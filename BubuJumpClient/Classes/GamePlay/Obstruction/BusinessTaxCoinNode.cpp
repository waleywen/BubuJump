#include "BusinessTaxCoinNode.h"

USING_NS_CC;

BusinessTaxCoinNode::~BusinessTaxCoinNode()
{

}

bool BusinessTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("BusinessTaxCoinNode.csb", "1.png"))
    {
        return false;
    }
    
    return true;
}
