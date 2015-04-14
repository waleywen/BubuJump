#include "TaxBibleUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "UIHelper.h"
#include "CommonUtility.h"

#include "Data/Network/NetworkManager.h"
#include "Data/Local/LoaclManager.h"

#include "MessageUILayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

TaxBibleContentUILayer::~TaxBibleContentUILayer()
{
    if (nullptr != this->_scrollView)
    {
        this->_scrollView->release();
        this->_scrollView = nullptr;
    }
    if (nullptr != this->_contentLabel)
    {
        this->_contentLabel->release();
        this->_contentLabel = nullptr;
    }
}

bool TaxBibleContentUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("TaxBibleContentUI.csb");
    this->addChild(uiNode);
    
    this->_scrollView = static_cast<ScrollView*>(UIHelper::seekNodeByName(this, "scrollView"));
    this->_scrollView->retain();
    this->_scrollView->setClippingEnabled(true);
    this->_scrollView->setClippingType(Layout::ClippingType::SCISSOR);
    
    auto backButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "backButton"));
    backButton->addClickEventListener(CC_CALLBACK_1(TaxBibleContentUILayer::backButtonClicked, this));

//    this->_contentLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "contentLabel"));
//    this->_contentLabel->retain();
//    this->_contentLabel->ignoreContentAdaptWithSize(true);
//    this->_contentLabel->setTextAreaSize(Size(620.0f, 0.0f));

    auto textLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "contentLabel"));
    textLabel->setVisible(false);
    this->_contentLabel = Label::create();
    this->_contentLabel->setDimensions(620.0f, 0.0f);
    this->_contentLabel->retain();
    this->_contentLabel->setPosition(textLabel->getPosition());
    this->_contentLabel->setSystemFontSize(textLabel->getFontSize());
    this->_contentLabel->setTextColor(textLabel->getTextColor());
    this->_contentLabel->setHorizontalAlignment(textLabel->getTextHorizontalAlignment());
    this->_contentLabel->setVerticalAlignment(textLabel->getTextVerticalAlignment());
    this->_contentLabel->setAnchorPoint(textLabel->getAnchorPoint());
    this->_scrollView->addChild(this->_contentLabel);
    
    return true;
}

void TaxBibleContentUILayer::setContentString(std::string contentString)
{
//    contentString = "\
//    1、大学生勤工助学，外出做家教取得劳动报酬，需要按照劳务报酬所得缴纳个人所得税。\n\
//    2、每月工资3500元及以上的个人，需要缴纳个人所得税。\n\
//    3、单位发放的购物礼品卡要缴纳个人所得税。\n\
//    4、一年收入超过12万元的个人，就需要自行申报缴纳个人所得税。\n\
//    5、企业所得税是对企业取得的所得进行征收税款的一个税种。\n\
//    6、深圳饮食、娱乐业有奖发票的最高奖金是20万元。\n\
//    7、城建税是随增值税、消费税、营业税“三税”同时附征的税。\n\
//    8、房屋出租需要缴纳房产税。\n\
//    9、个人自己居住的房屋不需要缴纳房产税。\n\
//    10、出租房屋的房产税是根据租金收入来计算的。\n\
//    11、学校自用的房产不需要缴纳房产税。\n\
//    12、契税是由购房人缴纳的。\n\
//    13、契税的应纳税额是根据成交价计算的。\n\
//    14、如果购买的是家庭的唯一住房，可以减免契税。\n\
//    15、房产证上加上配偶的名字，不需要交契税。\n\
//    16、父母的房产赠送给子女，需要交契税。\n\
//    17、摩托车需要缴纳车船税。\n\
//    18、游艇需要缴纳车船税。\n\
//    19、新能源车可以免征或者减半征收车船税。\n\
//    20、警用车船不需要缴纳车船税。";
//
//    this->_contentLabel->setString(contentString);
//    
//    Size contentLabelSize = this->_contentLabel->getContentSize();
//    if (1050.0f < contentLabelSize.height)
//    {
//        float newHeight = contentLabelSize.height + 50.0f;
//        this->_scrollView->setInnerContainerSize(Size(this->_scrollView->getContentSize().width, newHeight));
//        this->_contentLabel->setPosition(Point(this->_contentLabel->getPosition().x, newHeight - 25.0f));
//    }
    
    std::string contentString1 = "1、大学生勤工助学，外出做家教取得劳动报酬，需要按照劳务报酬所得缴纳个人所得税。\n2、每月工资3500元及以上的个人，需要缴纳个人所得税。\n3、单位发放的购物礼品卡要缴纳个人所得税。\n4、一年收入超过12万元的个人，就需要自行申报缴纳个人所得税。\n5、企业所得税是对企业取得的所得进行征收税款的一个税种。\n6、深圳饮食、娱乐业有奖发票的最高奖金是20万元。\n7、城建税是随增值税、消费税、营业税“三税”同时附征的税。\n8、房屋出租需要缴纳房产税。\n9、个人自己居住的房屋不需要缴纳房产税。\n10、出租房屋的房产税是根据租金收入来计算的。\n11、学校自用的房产不需要缴纳房产税。\n12、契税是由购房人缴纳的。\n13、契税的应纳税额是根据成交价计算的。\n14、如果购买的是家庭的唯一住房，可以减免契税。\n15、房产证上加上配偶的名字，不需要交契税。\n16、父母的房产赠送给子女，需要交契税。\n17、摩托车需要缴纳车船税。\n18、游艇需要缴纳车船税。\n19、新能源车可以免征或者减半征收车船税。\n20、警用车船不需要缴纳车船税。";
    this->_contentLabel->setString(contentString1);
    
    auto textLabel = static_cast<Text*>(UIHelper::seekNodeByName(this, "contentLabel"));
    auto contentLabel2 = Label::create();
    contentLabel2->setDimensions(620.0f, 0.0f);
    contentLabel2->setPosition(textLabel->getPosition().x, (this->_contentLabel->getContentSize().height + this->_contentLabel->getPosition().y));
    contentLabel2->setSystemFontSize(textLabel->getFontSize());
    contentLabel2->setTextColor(textLabel->getTextColor());
    contentLabel2->setHorizontalAlignment(textLabel->getTextHorizontalAlignment());
    contentLabel2->setVerticalAlignment(textLabel->getTextVerticalAlignment());
    contentLabel2->setAnchorPoint(textLabel->getAnchorPoint());
    this->_scrollView->addChild(contentLabel2);

    std::string contentString2 = "21、乘用车的排气量越大，车船税就要缴纳越多。\n22、房产的产权证需要缴纳印花税。\n23、个人将财产赠与学校所签订的合同，免征印花税。\n24、个人将财产赠与朋友所签订的合同，需要缴纳印花税。\n25、印花税票是以人民币为单位的。\n26、如果多贴了印花税票，可以申请退税。\n27、自家居住的房屋不需要缴纳城镇土地使用税。\n28、学校的用地可以免征城镇土地使用税。\n29、个人出租房产或销售住房不需要缴纳土地增值税。\n30、税务局为纳税人提供纳税咨询服务是免费的。\n31、个人在进行纳税申报时，可以不必本人亲自申报。\n32、国家向纳税人收税是无偿的。\n33、如果没有税收，政府机关不能正常运转。\n34、商家拒绝向消费者开具发票是违法行为。\n35、按照税种的不同，可以将发票分为增值税发票和普通发票。\n36、任何单位和个人不得转借、转让、代开发票。\n37、目前我国负责税收征管的主要政府机关是各地的国家税务局和地方税务局。\n38、要开办一家企业，就需要在规定的时间内到税务局办理税务登记手续。\n39、不经纳税人申报，税务机关不能直接到纳税人的银行账号里扣款收税。\n40、纳税人对税务机关作出的处罚，有上诉的权利。";
    
    contentLabel2->setString(contentString2);
    
    this->_contentLabel->setPosition(Point(this->_contentLabel->getPosition().x, this->_contentLabel->getContentSize().height + contentLabel2->getContentSize().height + 25));
    contentLabel2->setPosition(Point(this->_contentLabel->getPosition().x, contentLabel2->getContentSize().height + 25));

    this->_scrollView->setInnerContainerSize(Size(this->_scrollView->getContentSize().width, this->_contentLabel->getContentSize().height + contentLabel2->getContentSize().height + 50));
}

void TaxBibleContentUILayer::backButtonClicked(cocos2d::Ref *sender)
{
    Director::getInstance()->popScene();
}

TaxBibleUILayer::~TaxBibleUILayer()
{

}

bool TaxBibleUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("TaxBibleUI.csb");
    this->addChild(uiNode);
    
    auto scrollView = static_cast<ScrollView*>(UIHelper::seekNodeByName(this, "scrollView"));
    scrollView->setClippingEnabled(true);
    scrollView->setClippingType(Layout::ClippingType::SCISSOR);

    auto backButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "backButton"));
    backButton->addClickEventListener(CC_CALLBACK_1(TaxBibleUILayer::backButtonClicked, this));
    
    for (int i = 1; i <= 11; ++i)
    {
        std::string taxButtonName = "taxBibleUIButton";
        taxButtonName += CommonUtility::convertToString(i);
        auto taxButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, taxButtonName));
        taxButton->addClickEventListener(CC_CALLBACK_1(TaxBibleUILayer::taxButtonClicked, this));
    }
    
    return true;
}

void TaxBibleUILayer::backButtonClicked(cocos2d::Ref *sender)
{    
    Director::getInstance()->popScene();
}

void TaxBibleUILayer::taxButtonClicked(cocos2d::Ref *sender)
{
    TaxBibleContentUILayer* layer = TaxBibleContentUILayer::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    
    std::string contentString = "";
    
    ValueVector taxBibleVector = FileUtils::getInstance()->getValueVectorFromFile("TaxBible.plist");
    
    std::string taxButtonName = static_cast<Button*>(sender)->getName();
    if ("taxBibleUIButton1" == taxButtonName)
    {
        contentString = taxBibleVector.at(0).asString();
    }
    else if ("taxBibleUIButton2" == taxButtonName)
    {
        contentString = taxBibleVector.at(1).asString();
    }
    else if ("taxBibleUIButton3" == taxButtonName)
    {
        contentString = taxBibleVector.at(2).asString();
    }
    else if ("taxBibleUIButton4" == taxButtonName)
    {
        contentString = taxBibleVector.at(3).asString();
    }
    else if ("taxBibleUIButton5" == taxButtonName)
    {
        contentString = taxBibleVector.at(4).asString();
    }
    else if ("taxBibleUIButton6" == taxButtonName)
    {
        contentString = taxBibleVector.at(5).asString();
    }
    else if ("taxBibleUIButton7" == taxButtonName)
    {
        contentString = taxBibleVector.at(6).asString();
    }
    else if ("taxBibleUIButton8" == taxButtonName)
    {
        contentString = taxBibleVector.at(7).asString();
    }
    else if ("taxBibleUIButton9" == taxButtonName)
    {
        contentString = taxBibleVector.at(8).asString();
    }
    else if ("taxBibleUIButton10" == taxButtonName)
    {
        contentString = taxBibleVector.at(9).asString();
    }
    else if ("taxBibleUIButton11" == taxButtonName)
    {
        contentString = taxBibleVector.at(10).asString();
    }
    
    layer->setContentString(contentString);

    Director::getInstance()->pushScene(scene);
}
