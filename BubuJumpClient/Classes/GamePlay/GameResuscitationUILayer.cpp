#include "GameResuscitationUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "../AppMacros.h"
#include "../UIHelper.h"
#include "../CommonUtility.h"

#include "GamePlayLayer.h"
#include "GameTaxQAUILayer.h"
#include "GameOverUILayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

GameResuscitationUILayer::~GameResuscitationUILayer()
{
    if (nullptr != this->_coinLabel)
    {
        this->_coinLabel->release();
        this->_coinLabel = nullptr;
    }
    if (nullptr != this->_countDownSprite)
    {
        this->_countDownSprite->release();
        this->_countDownSprite = nullptr;
    }
}

bool GameResuscitationUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    LayerColor* layerColor = LayerColor::create(Color4B(166, 166, 166, 128), designResolutionSize.width, designResolutionSize.height);
    this->addChild(layerColor);
    
    auto uiNode = CSLoader::createNode("GameResuscitationUI.csb");
    this->addChild(uiNode);
    
    auto closeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "closeButton"));
    closeButton->addClickEventListener(CC_CALLBACK_1(GameResuscitationUILayer::closeButtonClicked, this));
    auto coinButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "coinButton"));
    coinButton->addClickEventListener(CC_CALLBACK_1(GameResuscitationUILayer::coinButtonClicked, this));
    auto qaButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "qaButton"));
    qaButton->addClickEventListener(CC_CALLBACK_1(GameResuscitationUILayer::qaButtonClicked, this));

    this->_coinLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "coinLabel"));
    this->_coinLabel->retain();
    this->_countDownSprite = static_cast<Sprite*>(UIHelper::seekNodeByName(uiNode, "countDownSprite"));
    this->_countDownSprite->retain();
    
    this->scheduleUpdate();

    return true;
}

void GameResuscitationUILayer::update(float delta)
{
    this->_countDown -= delta;
    
    if (this->_countDown <= 0.0f)
    {
        this->closeButtonClicked(nullptr);
        this->unscheduleUpdate();
        return;
    }

    if (this->getGamePlayLayer()->getCoinAmount() < this->getCurrentFee())
    {
        auto coinButton = static_cast<Button*>(UIHelper::seekNodeByName(this, "coinButton"));
        coinButton->setBright(false);
        coinButton->setEnabled(false);
    }
    
    this->_countDownSprite->setTexture(std::string("ready") + CommonUtility::convertToString(((int)(this->_countDown + 1))) + ".png");
}

void GameResuscitationUILayer::updateFee()
{
    this->_coinLabel->setString(CommonUtility::convertToString(this->getCurrentFee()));
}

void GameResuscitationUILayer::closeButtonClicked(cocos2d::Ref *sender)
{
    GameOverUILayer* layer = GameOverUILayer::create();
    layer->setTaxCoinAmount(this->getGamePlayLayer()->getTaxCoinAmount());
    layer->setMaxDistance(this->getGamePlayLayer()->getMaxDistance());
    layer->setTaxCoinMap(this->getGamePlayLayer()->getTaxCoinMap());
    auto scene = Scene::create();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
}

void GameResuscitationUILayer::coinButtonClicked(cocos2d::Ref *sender)
{
    this->getGamePlayLayer()->revive(this->getCurrentFee());
    
    Director::getInstance()->popScene();
}

void GameResuscitationUILayer::qaButtonClicked(cocos2d::Ref *sender)
{
    GameTaxQAUILayer* layer = GameTaxQAUILayer::create();
    layer->setGamePlayLayer(this->getGamePlayLayer());
    auto scene = Scene::create();
    scene->addChild(layer);
    
    Director::getInstance()->replaceScene(scene);
}

int GameResuscitationUILayer::getCurrentFee()
{
    int phase = this->getGamePlayLayer()->getTransitionPhase();
    if (0 == phase)
    {
        return 8000;
    }
    else if (1 == phase)
    {
        return 16000;
    }
    else
    {
        return 25000;
    }
}
