#include "JoinLotteryUILayer.h"

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

JoinLotteryUILayer::~JoinLotteryUILayer()
{
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
    if (nullptr != this->_backLayerColor)
    {
        this->_backLayerColor->release();
        this->_backLayerColor = nullptr;
    }
}

bool JoinLotteryUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    this->_backLayerColor = LayerColor::create(Color4B(166, 166, 166, 128), designResolutionSize.width, designResolutionSize.height);
    this->_backLayerColor->retain();
    auto _resultNodeEventListener = EventListenerTouchOneByOne::create();
    _resultNodeEventListener->setSwallowTouches(true);
    _resultNodeEventListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_resultNodeEventListener, this->_backLayerColor);
    this->addChild(this->_backLayerColor, -1);

    auto uiNode = CSLoader::createNode("JoinLotteryUI.csb");
    this->addChild(uiNode);
    
    auto closeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "closeButton"));
    closeButton->addClickEventListener(CC_CALLBACK_1(JoinLotteryUILayer::closeButtonClicked, this));
    auto submitButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "submitButton"));
    submitButton->addClickEventListener(CC_CALLBACK_1(JoinLotteryUILayer::submitButtonClicked, this));
    auto waitButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "waitButton"));
    waitButton->addClickEventListener(CC_CALLBACK_1(JoinLotteryUILayer::waitButtonClicked, this));
    auto changeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "changeButton"));
    changeButton->addClickEventListener(CC_CALLBACK_1(JoinLotteryUILayer::changeButtonClicked, this));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    EditBox* nameEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    nameEditBox->retain();
    nameEditBox->setPosition(Point(415.0f, 644.0f));
    nameEditBox->setFontSize(24);
    nameEditBox->setPlaceHolder("请输入姓名");
    nameEditBox->setInputMode(EditBox::InputMode::ANY);
    nameEditBox->setFontColor(Color3B::BLACK);
    nameEditBox->setText("");
    nameEditBox->setMaxLength(12);
    this->addChild(nameEditBox);
    this->_nameEditBox = nameEditBox;
    
    EditBox* phoneEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    phoneEditBox->retain();
    phoneEditBox->setPosition(Point(415.0f, 554.0f));
    phoneEditBox->setFontSize(24);
    phoneEditBox->setPlaceHolder("请输入数字");
    phoneEditBox->setInputMode(EditBox::InputMode::NUMERIC);
    phoneEditBox->setFontColor(Color3B::BLACK);
    phoneEditBox->setText("");
    phoneEditBox->setMaxLength(11);
    this->addChild(phoneEditBox);
    this->_phoneEditBox = phoneEditBox;
#else
    TextField* nameEditBox = TextField::create();
    nameEditBox->retain();
    nameEditBox->ignoreContentAdaptWithSize(false);
    nameEditBox->setTextAreaSize(Size(250.0f, 40.0f));
    nameEditBox->setPosition(Point(415.0f, 644.0f));
    nameEditBox->setFontSize(24);
    nameEditBox->setPlaceHolder("请输入姓名");
    nameEditBox->setTextColor(Color4B::BLACK);
    nameEditBox->setString("");
    nameEditBox->setTextHorizontalAlignment(TextHAlignment::LEFT);
    nameEditBox->setTextVerticalAlignment(TextVAlignment::CENTER);
    nameEditBox->setMaxLengthEnabled(true);
    nameEditBox->setMaxLength(12);
    nameEditBox->addEventListener(CC_CALLBACK_2(JoinLotteryUILayer::textFieldTapped, this));
    uiNode->addChild(nameEditBox);
    this->_nameEditBox = nameEditBox;
    
    TextField* phoneEditBox = TextField::create();
    phoneEditBox->retain();
    phoneEditBox->ignoreContentAdaptWithSize(false);
    phoneEditBox->setTextAreaSize(Size(250.0f, 40.0f));
    phoneEditBox->setPosition(Point(415.0f, 554.0f));
    phoneEditBox->setFontSize(24);
    phoneEditBox->setPlaceHolder("请输入数字");
    phoneEditBox->setTextColor(Color4B::BLACK);
    phoneEditBox->setString("");
    phoneEditBox->setTextHorizontalAlignment(TextHAlignment::LEFT);
    phoneEditBox->setTextVerticalAlignment(TextVAlignment::CENTER);
    phoneEditBox->setMaxLengthEnabled(true);
    phoneEditBox->setMaxLength(11);
    phoneEditBox->addEventListener(CC_CALLBACK_2(JoinLotteryUILayer::textFieldTapped, this));
    uiNode->addChild(phoneEditBox);
    this->_phoneEditBox = phoneEditBox;
#endif

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    if (false == gameSaveData.isDefaultName())
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        static_cast<EditBox*>(this->_nameEditBox)->setText(gameSaveData.getName().c_str());
#else
        static_cast<TextField*>(this->_nameEditBox)->setString(gameSaveData.getName());
#endif
        submitButton->setVisible(false);
        waitButton->setVisible(false);
    }
    else
    {
        changeButton->setVisible(false);
    }
    if (gameSaveData.getPhone().length() > 0)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        static_cast<EditBox*>(this->_phoneEditBox)->setText(gameSaveData.getPhone().c_str());
#else
        static_cast<TextField*>(this->_phoneEditBox)->setString(gameSaveData.getPhone());
#endif
    }
    
    return true;
}

void JoinLotteryUILayer::closeButtonClicked(cocos2d::Ref *sender)
{    
    this->removeFromParent();
}

void JoinLotteryUILayer::submitButtonClicked(cocos2d::Ref *sender)
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
                
        MessageUILayer::create(2.0f, this->getParent(), "感谢参与！", Size(500.0f, 250.0f));
        this->removeFromParent();
    }
}

void JoinLotteryUILayer::waitButtonClicked(cocos2d::Ref *sender)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    gameSaveData.setNeedShowJoinLotteryUI(false);
    LoaclManager::getInstance()->save();
    
    this->removeFromParent();
}

void JoinLotteryUILayer::changeButtonClicked(cocos2d::Ref *sender)
{
    this->submitButtonClicked(sender);
}

void JoinLotteryUILayer::textFieldTapped(cocos2d::Ref *, cocos2d::ui::TextField::EventType eventType)
{
    if (TextField::EventType::ATTACH_WITH_IME == eventType)
    {
        this->_nameEditBox->getParent()->setPosition(Vec2(0.0f, 300.0f));
    }
    else if (TextField::EventType::DETACH_WITH_IME == eventType)
    {
        this->_nameEditBox->getParent()->setPosition(Vec2(0.0f, 0.0f));
    }
}
