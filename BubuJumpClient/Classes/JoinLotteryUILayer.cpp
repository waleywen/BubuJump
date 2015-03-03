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

    this->_nameEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    this->_nameEditBox->retain();
    this->_nameEditBox->setPosition(Point(415.0f, 644.0f));
    this->_nameEditBox->setFontSize(24);
    this->_nameEditBox->setPlaceHolder("请输入姓名");
    this->_nameEditBox->setInputMode(EditBox::InputMode::ANY);
    this->_nameEditBox->setFontColor(Color3B::BLACK);
    this->_nameEditBox->setText("");
    this->_nameEditBox->setMaxLength(12);
    this->addChild(this->_nameEditBox);
    
    this->_phoneEditBox = EditBox::create(Size(250.0f, 40.0f), Scale9Sprite::create());
    this->_phoneEditBox->retain();
    this->_phoneEditBox->setPosition(Point(415.0f, 554.0f));
    this->_phoneEditBox->setFontSize(24);
    this->_phoneEditBox->setPlaceHolder("请输入数字");
    this->_phoneEditBox->setInputMode(EditBox::InputMode::NUMERIC);
    this->_phoneEditBox->setFontColor(Color3B::BLACK);
    this->_phoneEditBox->setText("");
    this->_phoneEditBox->setMaxLength(11);
    this->addChild(this->_phoneEditBox);

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    if (false == gameSaveData.isDefaultName())
    {
        this->_nameEditBox->setText(gameSaveData.getName().c_str());
    }
    if (gameSaveData.getPhone().length() > 0)
    {
        this->_phoneEditBox->setText(gameSaveData.getPhone().c_str());
    }
    
    return true;
}

void JoinLotteryUILayer::closeButtonClicked(cocos2d::Ref *sender)
{    
    this->removeFromParent();
}

void JoinLotteryUILayer::submitButtonClicked(cocos2d::Ref *sender)
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
