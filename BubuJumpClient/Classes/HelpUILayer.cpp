#include "HelpUILayer.h"

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

HelpUILayer::~HelpUILayer()
{
    if (nullptr != this->_pageNode1)
    {
        this->_pageNode1->release();
        this->_pageNode1 = nullptr;
    }
    if (nullptr != this->_pageNode2)
    {
        this->_pageNode2->release();
        this->_pageNode2 = nullptr;
    }
    if (nullptr != this->_pageNode3)
    {
        this->_pageNode3->release();
        this->_pageNode3 = nullptr;
    }
    if (nullptr != this->_lotteryNode)
    {
        this->_lotteryNode->release();
        this->_lotteryNode = nullptr;
    }
    if (nullptr != this->_leftArrowButton)
    {
        this->_leftArrowButton->release();
        this->_leftArrowButton = nullptr;
    }
    if (nullptr != this->_rightArrowButton)
    {
        this->_rightArrowButton->release();
        this->_rightArrowButton = nullptr;
    }
    if (nullptr != this->_nameEditBox)
    {
        this->_nameEditBox->release();
        this->_nameEditBox = nullptr;
    }
    if (nullptr != this->_phoneEditBox)
    {
        this->_phoneEditBox->release();
        this->_phoneEditBox = nullptr;
    }
}

bool HelpUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("HelpUI.csb");
    this->addChild(uiNode);
    
    this->_pageNode1 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "pageNode1"));
    this->_pageNode1->retain();
    this->_pageNode2 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "pageNode2"));
    this->_pageNode2->retain();
    this->_pageNode3 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "pageNode3"));
    this->_pageNode3->retain();
    this->_lotteryNode = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "lotteryNode"));
    this->_lotteryNode->retain();
    this->_leftArrowButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "leftArrowButton"));
    this->_leftArrowButton->retain();
    _leftArrowButton->addClickEventListener(CC_CALLBACK_1(HelpUILayer::leftArrowButtonClicked, this));
    this->_rightArrowButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "rightArrowButton"));
    this->_rightArrowButton->retain();
    _rightArrowButton->addClickEventListener(CC_CALLBACK_1(HelpUILayer::rightArrowButtonClicked, this));

    auto backButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "backButton"));
    backButton->addClickEventListener(CC_CALLBACK_1(HelpUILayer::backButtonClicked, this));
    auto confirmButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "confirmButton"));
    confirmButton->addClickEventListener(CC_CALLBACK_1(HelpUILayer::confirmButtonClicked, this));
    
    this->_nameEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    this->_nameEditBox->retain();
    this->_nameEditBox->setPosition(Point(415.0f, 302.0f));
    this->_nameEditBox->setFontSize(24);
    this->_nameEditBox->setPlaceHolder("请输入姓名");
    this->_nameEditBox->setInputMode(EditBox::InputMode::ANY);
    this->_nameEditBox->setFontColor(Color3B::BLACK);
    this->_nameEditBox->setText("");
    this->_nameEditBox->setMaxLength(12);
    this->_lotteryNode->addChild(this->_nameEditBox);
    
    this->_phoneEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    this->_phoneEditBox->retain();
    this->_phoneEditBox->setPosition(Point(415.0f, 213.0f));
    this->_phoneEditBox->setFontSize(24);
    this->_phoneEditBox->setPlaceHolder("请输入数字");
    this->_phoneEditBox->setInputMode(EditBox::InputMode::NUMERIC);
    this->_phoneEditBox->setFontColor(Color3B::BLACK);
    this->_phoneEditBox->setText("");
    this->_phoneEditBox->setMaxLength(11);
    this->_lotteryNode->addChild(this->_phoneEditBox);

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    if (false == gameSaveData.isDefaultName() || gameSaveData.getPhone().length() > 0)
    {
        this->_lotteryNode->setVisible(false);
    }
    
    this->showPage(0);
    
    return true;
}

void HelpUILayer::backButtonClicked(cocos2d::Ref *sender)
{    
    Director::getInstance()->popScene();
}

void HelpUILayer::leftArrowButtonClicked(cocos2d::Ref *sender)
{
    this->showPage(this->_currentPageIndex - 1);
}

void HelpUILayer::rightArrowButtonClicked(cocos2d::Ref *sender)
{
    this->showPage(this->_currentPageIndex + 1);
}

void HelpUILayer::confirmButtonClicked(cocos2d::Ref *sender)
{
    std::string name = this->_nameEditBox->getText();
    std::string phone = this->_phoneEditBox->getText();
    CommonUtility::trim(name);
    CommonUtility::trim(phone);

    if (0 == name.length())
    {
        MessageUILayer::create(2.0f, this, "请填写您的真实姓名", Size(500.0f, 250.0f));
    }
    else if (0 == phone.length())
    {
        MessageUILayer::create(2.0f, this, "请填写有效手机号码", Size(500.0f, 250.0f));
    }
    else if (false == CommonUtility::checkMobilePhoneNumber(phone))
    {
        MessageUILayer::create(2.0f, this, "您填写的手机号码有误", Size(500.0f, 250.0f));
    }
    else
    {
        GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
        gameSaveData.setName(name);
        gameSaveData.setPhone(phone);
        LoaclManager::getInstance()->save();
        NetworkManager::getInstance()->joinLottery();
        
        this->_lotteryNode->setVisible(false);

        MessageUILayer::create(2.0f, this->getParent(), "感谢参与！", Size(500.0f, 250.0f));
    }
}

void HelpUILayer::showPage(int index)
{
    if (index < 0)
    {
        index = 0;
    }
    if (index > 2)
    {
        index = 2;
    }
    
    this->_currentPageIndex = index;
    
    this->_leftArrowButton->setVisible(true);
    this->_rightArrowButton->setVisible(true);

    if (0 == this->_currentPageIndex)
    {
        this->_leftArrowButton->setVisible(false);
    }
    if (2 == this->_currentPageIndex)
    {
        this->_rightArrowButton->setVisible(false);
    }
    
    switch (this->_currentPageIndex) {
        case 0:
            this->_pageNode1->setPosition(Vec2::ZERO);
            this->_pageNode2->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode3->setPosition(Vec2(-1000.0f, -1000.0f));
            break;
        case 1:
            this->_pageNode1->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode2->setPosition(Vec2::ZERO);
            this->_pageNode3->setPosition(Vec2(-1000.0f, -1000.0f));
            break;
        case 2:
            this->_pageNode1->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode2->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode3->setPosition(Vec2::ZERO);
            break;
            
        default:
            break;
    }
}
