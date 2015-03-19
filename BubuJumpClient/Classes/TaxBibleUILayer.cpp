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
