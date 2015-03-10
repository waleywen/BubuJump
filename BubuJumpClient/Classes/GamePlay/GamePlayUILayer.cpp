#include "GamePlayUILayer.h"

#include "AppMacros.h"

#include "cocostudio/CocoStudio.h"

#include "../UIHelper.h"
#include "../CommonUtility.h"
#include "GamePauseUILayer.h"

#include "Obstruction/Effect/BaseEffect.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

GamePlayUILayer::~GamePlayUILayer()
{
    if (nullptr != this->_coinAmountLabel)
    {
        this->_coinAmountLabel->release();
        this->_coinAmountLabel = nullptr;
    }
    if (nullptr != this->_heartLabel)
    {
        this->_heartLabel->release();
        this->_heartLabel = nullptr;
    }
    if (nullptr != this->_distanceLabel)
    {
        this->_distanceLabel->release();
        this->_distanceLabel = nullptr;
    }
    if (nullptr != this->_propSprite)
    {
        this->_propSprite->release();
        this->_propSprite = nullptr;
    }
}

bool GamePlayUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("GamePlayUI.csb");
    this->addChild(uiNode);

    //groundSprite->setPosition(Vec2(designResolutionSize / 2) + Vec2(0.0f, (designResolutionSize.height - this->_visibleSize.height) / 2.0f));

    auto topBar = UIHelper::seekNodeByTag(uiNode, 101);
    auto bottomBar = UIHelper::seekNodeByTag(uiNode, 199);
    
    topBar->setPosition(topBar->getPosition().x, topBar->getPosition().y - (designResolutionSize.height - Director::getInstance()->getVisibleSize().height) / 2.0f);
    bottomBar->setPosition(bottomBar->getPosition().x, bottomBar->getPosition().y + (designResolutionSize.height - Director::getInstance()->getVisibleSize().height) / 2.0f);
    
    this->_coinAmountLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "coinAmountLabel"));
    this->_coinAmountLabel->retain();
    this->_heartLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "heartLabel"));
    this->_heartLabel->retain();
    this->_distanceLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "distanceLabel"));
    this->_distanceLabel->retain();
    
    this->_coinAmountLabel->setString("0");
    this->_heartLabel->setString("0");
    this->_distanceLabel->setString("0");
    
    this->_propSprite = static_cast<Sprite*>(UIHelper::seekNodeByName(uiNode, "propSprite"));
    this->_propSprite->retain();
    this->_propSprite->setVisible(false);
    
    auto pauseButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "pauseButton"));
    pauseButton->addClickEventListener(CC_CALLBACK_1(GamePlayUILayer::pauseButtonClicked, this));
    
    auto readyNode = CSLoader::createNode("Ready.csb");
    readyNode->setPosition(designResolutionSize / 2.0f);
    this->addChild(readyNode);
    auto actionTimeline = CSLoader::createTimeline("Ready.csb");
    
    readyNode->runAction(actionTimeline);
    actionTimeline->gotoFrameAndPlay(0, false);

    return true;
}

void GamePlayUILayer::gameUpdate(float delta)
{
    this->_heartLabel->setString(CommonUtility::convertToString(this->_heartCount));

    const int addCoinPerSecond = 100;
    const float addDistancePerSecond = 1000.0f;
    if (this->_currentCoinAmount < this->_coinAmount)
    {
        int increasement = 0;
        if (this->_coinAmount > (this->_currentCoinAmount + addCoinPerSecond))
        {
            increasement = (this->_coinAmount - this->_currentCoinAmount - addCoinPerSecond);
        }
        else
        {
            increasement = addCoinPerSecond * delta;
        }
        this->_currentCoinAmount += increasement;
        if (this->_currentCoinAmount > this->_coinAmount)
        {
            this->_currentCoinAmount = this->_coinAmount;
        }
        this->_coinAmountLabel->setString(CommonUtility::convertToString(this->_currentCoinAmount));
    }
    else if (this->_currentCoinAmount > this->_coinAmount)
    {
        this->_currentCoinAmount = this->_coinAmount;
        this->_coinAmountLabel->setString(CommonUtility::convertToString(this->_currentCoinAmount));
    }
    if (this->_currentDistance < this->_maxDistance)
    {
        float increasement = 0;
        if (this->_maxDistance > (this->_currentDistance + addDistancePerSecond))
        {
            increasement = (this->_maxDistance - this->_currentDistance - addDistancePerSecond);
        }
        else
        {
            increasement = addDistancePerSecond * delta;
        }
        this->_currentDistance += increasement;
        if (this->_currentDistance > this->_maxDistance)
        {
            this->_currentDistance = this->_maxDistance;
        }
        this->_distanceLabel->setString(CommonUtility::convertToString((int)this->_currentDistance));
    }
    
    if (nullptr != this->getEffect() && this->getEffect()->getState() == ActivatedEffectState)
    {
        float leftTime = this->getEffect()->getTime() - this->getEffect()->getDuration();
        
        bool shouldShowIcon = true;
        if (FlyBootEffectType == this->getEffect()->getType())
        {
            this->_propSprite->setTexture("FlyBoot.png");
        }
        else if (RocketEffectType == this->getEffect()->getType())
        {
            this->_propSprite->setTexture("Rocket.png");
        }
        else if (MagnetEffectType == this->getEffect()->getType())
        {
            this->_propSprite->setTexture("Magnet.png");
        }
        else if (AngelWingEffectType == this->getEffect()->getType())
        {
            this->_propSprite->setTexture("AngelWing.png");
        }
        else if (EvilCloudEffectType == this->getEffect()->getType())
        {
            this->_propSprite->setTexture("EvilCloud.png");
        }
        else
        {
            shouldShowIcon = false;
        }
        
        if (true == shouldShowIcon)
        {
            if (leftTime < 3.0f)
            {
                if ((leftTime - (int)leftTime) <= 0.5f)
                {
                    this->_propSprite->setVisible(true);
                }
                else
                {
                    this->_propSprite->setVisible(false);
                }
            }
            else
            {
                this->_propSprite->setVisible(true);
            }
        }
        else
        {
            this->_propSprite->setVisible(false);
        }
    }
    else
    {
        this->_propSprite->setVisible(false);
    }
}

void GamePlayUILayer::pauseButtonClicked(cocos2d::Ref *sender)
{
    RenderTexture *renderTexture = RenderTexture::create(designResolutionSize.width, designResolutionSize.height);
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();
    renderTexture->setPosition(designResolutionSize / 2.0f);
    
    auto gamePauseUILayer = GamePauseUILayer::create();
    gamePauseUILayer->setCoinAmount(this->_coinAmount);
    gamePauseUILayer->setMaxDistance(this->_maxDistance);
    
    auto scene = Scene::create();
    scene->addChild(renderTexture);
    scene->addChild(gamePauseUILayer);
    Director::getInstance()->pushScene(scene);
}
