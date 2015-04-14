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
    if (nullptr != this->_pageNode4)
    {
        this->_pageNode4->release();
        this->_pageNode4 = nullptr;
    }
    if (nullptr != this->_pageNode5)
    {
        this->_pageNode5->release();
        this->_pageNode5 = nullptr;
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
    this->_eventDispatcher->removeEventListenersForTarget(this);
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
    this->_pageNode4 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "pageNode4"));
    this->_pageNode4->retain();
    this->_pageNode5 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "pageNode5"));
    this->_pageNode5->retain();
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
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    EditBox* nameEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    nameEditBox->retain();
    nameEditBox->setPosition(Point(415.0f, 506.0f));
    nameEditBox->setFontSize(24);
    nameEditBox->setPlaceHolder("请输入姓名");
    nameEditBox->setInputMode(EditBox::InputMode::ANY);
    nameEditBox->setFontColor(Color3B::BLACK);
    nameEditBox->setText("");
    nameEditBox->setMaxLength(12);
    this->_lotteryNode->addChild(nameEditBox);
    this->_nameEditBox = nameEditBox;
    
    EditBox* phoneEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    phoneEditBox->retain();
    phoneEditBox->setPosition(Point(415.0f, 417.0f));
    phoneEditBox->setFontSize(24);
    phoneEditBox->setPlaceHolder("请输入数字");
    phoneEditBox->setInputMode(EditBox::InputMode::NUMERIC);
    phoneEditBox->setFontColor(Color3B::BLACK);
    phoneEditBox->setText("");
    phoneEditBox->setMaxLength(11);
    this->_lotteryNode->addChild(phoneEditBox);
    this->_phoneEditBox = phoneEditBox;    
#else
    TextField* nameEditBox = TextField::create();
    nameEditBox->retain();
    nameEditBox->ignoreContentAdaptWithSize(false);
    nameEditBox->setTextAreaSize(Size(250.0f, 40.0f));
    nameEditBox->setPosition(Point(415.0f, 506.0f));
    nameEditBox->setFontSize(24);
    nameEditBox->setPlaceHolder("请输入姓名");
    nameEditBox->setTextColor(Color4B::BLACK);
    nameEditBox->setString("");
    nameEditBox->setTextHorizontalAlignment(TextHAlignment::LEFT);
    nameEditBox->setTextVerticalAlignment(TextVAlignment::CENTER);
    nameEditBox->setMaxLengthEnabled(true);
    nameEditBox->setMaxLength(12);
    nameEditBox->addEventListener(CC_CALLBACK_2(HelpUILayer::textFieldTapped, this));
    this->_lotteryNode->addChild(nameEditBox);
    this->_nameEditBox = nameEditBox;
    
    TextField* phoneEditBox = TextField::create();
    phoneEditBox->retain();
    phoneEditBox->ignoreContentAdaptWithSize(false);
    phoneEditBox->setTextAreaSize(Size(250.0f, 40.0f));
    phoneEditBox->setPosition(Point(415.0f, 417.0f));
    phoneEditBox->setFontSize(24);
    phoneEditBox->setPlaceHolder("请输入数字");
    phoneEditBox->setTextColor(Color4B::BLACK);
    phoneEditBox->setString("");
    phoneEditBox->setTextHorizontalAlignment(TextHAlignment::LEFT);
    phoneEditBox->setTextVerticalAlignment(TextVAlignment::CENTER);
    phoneEditBox->setMaxLengthEnabled(true);
    phoneEditBox->setMaxLength(11);
    phoneEditBox->addEventListener(CC_CALLBACK_2(HelpUILayer::textFieldTapped, this));
    this->_lotteryNode->addChild(phoneEditBox);
    this->_phoneEditBox = phoneEditBox;
#endif

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    if (false == gameSaveData.isDefaultName() || gameSaveData.getPhone().length() > 0)
    {
        this->_lotteryNode->setVisible(false);
    }
    
    this->showPage(0);
    
    auto resultNodeEventListener = EventListenerTouchOneByOne::create();
    resultNodeEventListener->setSwallowTouches(true);
    resultNodeEventListener->onTouchBegan = CC_CALLBACK_2(HelpUILayer::touchBegan, this);
    resultNodeEventListener->onTouchEnded = CC_CALLBACK_2(HelpUILayer::touchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(resultNodeEventListener, this);
    
    return true;
}

bool HelpUILayer::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->_beginPoint = touch->getLocation();
    return true;
}

void HelpUILayer::touchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point endPoint = touch->getLocation();
    
    float d = (this->_beginPoint - endPoint).length();
    if (d > 20.0f)
    {
        if (this->_beginPoint.x-endPoint.x<0&&this->_beginPoint.x-endPoint.x<this->_beginPoint.y-endPoint.y&&endPoint.x-this->_beginPoint.x>this->_beginPoint.y-endPoint.y)
        {
//            touchRight();
            this->leftArrowButtonClicked(nullptr);
        }
        if (this->_beginPoint.x-endPoint.x>0&&this->_beginPoint.x-endPoint.x>this->_beginPoint.y-endPoint.y&&endPoint.x-this->_beginPoint.x<this->_beginPoint.y-endPoint.y)
        {
//            touchLeft();
            this->rightArrowButtonClicked(nullptr);
        }
        
        if (this->_beginPoint.y-endPoint.y<0&&this->_beginPoint.y-endPoint.y<this->_beginPoint.x-endPoint.x&&endPoint.y-this->_beginPoint.y>this->_beginPoint.x-endPoint.x)
        {
//            touchUp();
        }
        if (this->_beginPoint.y-endPoint.y>0&&this->_beginPoint.y-endPoint.y>this->_beginPoint.x-endPoint.x&&endPoint.y-this->_beginPoint.y<this->_beginPoint.x-endPoint.x)
        {
//            touchDown();
        }
    }
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string name = static_cast<EditBox*>(this->_nameEditBox)->getText();
    std::string phone = static_cast<EditBox*>(this->_phoneEditBox)->getText();
#else
    std::string name = static_cast<TextField*>(this->_nameEditBox)->getString();
    std::string phone = static_cast<TextField*>(this->_phoneEditBox)->getString();
#endif
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
        MessageUILayer::create(2.0f, this, "您填写的手机号码\n有误", Size(500.0f, 250.0f));
    }
    else
    {
        GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
        gameSaveData.setName(name);
        gameSaveData.setPhone(phone);
        gameSaveData.setNeedShowJoinLotteryUI(false);
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
    if (index > 4)
    {
        index = 4;
    }
    
    this->_currentPageIndex = index;
    
    this->_leftArrowButton->setVisible(true);
    this->_rightArrowButton->setVisible(true);

    if (0 == this->_currentPageIndex)
    {
        this->_leftArrowButton->setVisible(false);
    }
    if (4 == this->_currentPageIndex)
    {
        this->_rightArrowButton->setVisible(false);
    }
    
    switch (this->_currentPageIndex) {
        case 0:
            this->_pageNode1->setPosition(Vec2::ZERO);
            this->_pageNode2->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode3->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode4->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode5->setPosition(Vec2(-1000.0f, -1000.0f));
            break;
        case 1:
            this->_pageNode1->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode2->setPosition(Vec2::ZERO);
            this->_pageNode3->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode4->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode5->setPosition(Vec2(-1000.0f, -1000.0f));
            break;
        case 2:
            this->_pageNode1->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode2->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode3->setPosition(Vec2::ZERO);
            this->_pageNode4->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode5->setPosition(Vec2(-1000.0f, -1000.0f));
            break;
        case 3:
            this->_pageNode1->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode2->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode3->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode4->setPosition(Vec2::ZERO);
            this->_pageNode5->setPosition(Vec2(-1000.0f, -1000.0f));
            break;
        case 4:
            this->_pageNode1->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode2->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode3->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode4->setPosition(Vec2(-1000.0f, -1000.0f));
            this->_pageNode5->setPosition(Vec2::ZERO);
            break;
            
        default:
            break;
    }
}

void HelpUILayer::textFieldTapped(cocos2d::Ref *, cocos2d::ui::TextField::EventType eventType)
{
    if (TextField::EventType::ATTACH_WITH_IME == eventType)
    {
        this->setPosition(Vec2(0.0f, 550.0f));
    }
    else if (TextField::EventType::DETACH_WITH_IME == eventType)
    {
        this->setPosition(Vec2(0.0f, 0.0f));
    }
}
