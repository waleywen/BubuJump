#include "UrbanLandUseTaxCoinNode.h"

USING_NS_CC;

UrbanLandUseTaxCoinNode::~UrbanLandUseTaxCoinNode()
{

}

bool UrbanLandUseTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("UrbanLandUseTaxCoinNode.csb", "UrbanLandUseTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
