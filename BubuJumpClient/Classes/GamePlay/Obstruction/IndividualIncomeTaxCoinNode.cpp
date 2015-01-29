#include "IndividualIncomeTaxCoinNode.h"

USING_NS_CC;

IndividualIncomeTaxCoinNode::~IndividualIncomeTaxCoinNode()
{

}

bool IndividualIncomeTaxCoinNode::init()
{
    if (false == TaxCoinNode::initWithCsbNameAndTipsName("IndividualIncomeTaxCoinNode.csb", "1.png"))
    {
        return false;
    }
    
    return true;
}
