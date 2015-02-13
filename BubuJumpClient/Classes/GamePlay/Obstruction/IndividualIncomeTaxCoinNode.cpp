#include "IndividualIncomeTaxCoinNode.h"

USING_NS_CC;

IndividualIncomeTaxCoinNode::~IndividualIncomeTaxCoinNode()
{

}

bool IndividualIncomeTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("IndividualIncomeTaxCoinNode.csb", "IndividualIncomeTaxAddTips.png"))
    {
        return false;
    }
    
    return true;
}
