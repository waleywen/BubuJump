#include "StampTaxCoinNode.h"

USING_NS_CC;

StampTaxCoinNode::~StampTaxCoinNode()
{

}

bool StampTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("StampTaxCoinNode.csb", "1.png"))
    {
        return false;
    }
    
    return true;
}