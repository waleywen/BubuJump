#include "GamePauseUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "../UIHelper.h"
#include "../CommonUtility.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

GamePauseUILayer::~GamePauseUILayer()
{
    if (nullptr != this->_coinAmountLabel)
    {
        this->_coinAmountLabel->release();
        this->_coinAmountLabel = nullptr;
    }
    if (nullptr != this->_distanceLabel)
    {
        this->_distanceLabel->release();
        this->_distanceLabel = nullptr;
    }
}

bool GamePauseUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("GamePauseUI.csb");
    this->addChild(uiNode);
    
    this->_coinAmountLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "coinAmountLabel"));
    this->_coinAmountLabel->retain();
    this->_distanceLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "distanceLabel"));
    this->_distanceLabel->retain();

    auto continueButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "continueButton"));
    continueButton->addClickEventListener(CC_CALLBACK_1(GamePauseUILayer::continueButtonClicked, this));

    return true;
}

void GamePauseUILayer::setCoinAmount(int coinAmount)
{
    this->_coinAmountLabel->setString(CommonUtility::convertToString(coinAmount));
}

void GamePauseUILayer::setMaxDistance(float maxDistance)
{
    this->_distanceLabel->setString(CommonUtility::convertToString((int)maxDistance));
}

void GamePauseUILayer::continueButtonClicked(cocos2d::Ref *sender)
{
    Director::getInstance()->popScene();
}
