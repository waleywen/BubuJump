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
    
    this->_contentLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "contentLabel"));
    this->_contentLabel->retain();
    
    return true;
}

void TaxBibleContentUILayer::setContentString(std::string contentString)
{
    this->_contentLabel->setString(contentString);
    
    Size contentLabelSize = this->_contentLabel->getContentSize();
    if (1050.0f < contentLabelSize.height)
    {
        float newHeight = contentLabelSize.height + 50.0f;
        this->_scrollView->setInnerContainerSize(Size(this->_scrollView->getContentSize().width, newHeight));
        this->_contentLabel->setPosition(Point(this->_contentLabel->getPosition().x, newHeight - 25.0f));
    }
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
    
//    for (int i = 0; i < 30; ++i)
//    {
//        contentString += "Test\n";
//    }
    
    std::string taxButtonName = static_cast<Button*>(sender)->getName();
    if ("taxBibleUIButton1" == taxButtonName)
    {
        contentString = "一、个人所得税：\n\n1、目前我国个人取得所得应缴纳个\n人所得税的项目有11种\n\n2、取得的工资需要缴纳个人所得税\n\n3、单位发放的购物礼品卡要缴纳个\n人所得税\n\n4、年所得超过12万元万元的纳税人\n需要自行申报纳税";
    }
    else if ("taxBibleUIButton2" == taxButtonName)
    {
        contentString = "二、企业所得税\n\n6、企业所得税是依法对企业取得的\n所得进行征收税款的一个税种\n\n8、法人企业是企业所得税的纳税人\n\n9、企业所得税的税率为25%。\n\n10、企业所得税的征税对象是对所\n得征收";
    }
    else if ("taxBibleUIButton3" == taxButtonName)
    {
        contentString = "三、营业税\n\n11、在深圳，深圳市地方税务局是\n营业税的征收机关\n\n13、1%不属于营业税税率\n\n14、深圳饮食、娱乐业有奖发票的最\n高奖金是20万元\n\n16、根据相关规定，月营业额不超过\n3万元的营业税纳税人免征营业税。";
    }
    else if ("taxBibleUIButton4" == taxButtonName)
    {
        contentString = "四、城市维护建设税\n\n18、城建税的全称是城市维护建设\n税。\n\n21、营改增的全称是营业税改征增值\n税。\n\n22、营业税是对在中国境内提供应税\n劳务、转让无形资产或销售不动产的\n单位和个人，就其所取得的营业额征\n收的一种税。\n\n23、城建税是以增值税、消费税、营\n业税“三税”实际缴纳的税额为计算依\n据，随“三税”同时附征。";
    }
    else if ("taxBibleUIButton5" == taxButtonName)
    {
        contentString = "五、印花税\n\n24、个人购买住房不需要缴纳印花税\n\n25、个人购买商铺缴纳印花税的税率\n是万分之五\n\n26、身份证属于印花税的征税范围\n\n27、购销合同印花税的税率是万分之\n三\n\n28、按税法规定可以免缴印花税的凭\n证是无息贷款合同\n\n29、财产所有人将财产捐给私营企业\n所书立的书据，应该缴纳印花税\n\n30、个人将财产赠与学校所书立的合\n同，免征印花税\n\n31、个人将财产赠与朋友所书立的合\n同，应征印花税\n\n32、书立各类经济合同时，以合同当\n事人为印花税的纳税人\n\n35、商品买卖合同按照购销合同征收\n印花税\n\n36、借款合同的印花税税率为万分之\n零点五\n\n37、印花税主要是针对部分经济合同\n征收的一种税\n\n38、印花税票是以人民币为单位的\n\n39、财产租赁合同需要征收印花税";
    }
    else if ("taxBibleUIButton6" == taxButtonName)
    {
        contentString = "";
    }
    else if ("taxBibleUIButton7" == taxButtonName)
    {
        contentString = "";
    }
    else if ("taxBibleUIButton8" == taxButtonName)
    {
        contentString = "";
    }
    else if ("taxBibleUIButton9" == taxButtonName)
    {
        contentString = "";
    }
    else if ("taxBibleUIButton10" == taxButtonName)
    {
        contentString = "";
    }
    else if ("taxBibleUIButton11" == taxButtonName)
    {
        contentString = "";
    }
    
    layer->setContentString(contentString);

    Director::getInstance()->pushScene(scene);
}
