#include "LeaderboardUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "UIHelper.h"
#include "CommonUtility.h"
#include "JoinLotteryUILayer.h"
#include "Data/Network/NetworkManager.h"
#include "Data/Local/LoaclManager.h"
#include "Social/SocialManager.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

LeaderboardUILayer::~LeaderboardUILayer()
{
    if (nullptr != this->_loadingSprite)
    {
        this->_loadingSprite->release();
        this->_loadingSprite = nullptr;
    }
    if (nullptr != this->_taxCoinAmountLabel)
    {
        this->_taxCoinAmountLabel->release();
        this->_taxCoinAmountLabel = nullptr;
    }
    if (nullptr != this->_distanceLabel)
    {
        this->_distanceLabel->release();
        this->_distanceLabel = nullptr;
    }
    if (nullptr != this->_myNameLabel)
    {
        this->_myNameLabel->release();
        this->_myNameLabel = nullptr;
    }
}

bool LeaderboardUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("LeaderboardUI.csb");
    this->addChild(uiNode);
    
    this->_taxCoinAmountLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "taxCoinAmountLabel"));
    this->_taxCoinAmountLabel->retain();
    this->_distanceLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "distanceLabel"));
    this->_distanceLabel->retain();

    auto shareButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "shareButton"));
    shareButton->addClickEventListener(CC_CALLBACK_1(LeaderboardUILayer::shareButtonClicked, this));
    auto okButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "okButton"));
    okButton->addClickEventListener(CC_CALLBACK_1(LeaderboardUILayer::okButtonClicked, this));
    auto homeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "homeButton"));
    homeButton->addClickEventListener(CC_CALLBACK_1(LeaderboardUILayer::homeButtonClicked, this));
    auto drawButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "drawButton"));
    drawButton->addClickEventListener(CC_CALLBACK_1(LeaderboardUILayer::drawButtonClicked, this));

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    
    this->_loadingSprite = Sprite::create("loading.png");
    this->_loadingSprite->retain();
    this->_loadingSprite->setPosition(Vec2(360.0f, 400.0f));
    auto sequenceAction = Sequence::create(RotateTo::create(2, 180), RotateTo::create(2, 360), NULL);
    this->_loadingSprite->runAction(Repeat::create(sequenceAction, pow(2,30)));
    this->addChild(this->_loadingSprite);
    
    this->_requestIndex = NetworkManager::getInstance()->requestLeaderboard(CC_CALLBACK_1(LeaderboardUILayer::leaderboardRequested, this));
    
    this->_taxCoinAmountLabel->setString(CommonUtility::convertToString(gameSaveData.getMaxTaxCoinAmount()));
    this->_distanceLabel->setString(CommonUtility::convertToString(gameSaveData.getMaxDistance()));

    this->scheduleUpdate();
    
    return true;
}

void LeaderboardUILayer::update(float delta)
{
    if (nullptr != this->_myNameLabel)
    {
        GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
        if (false == gameSaveData.isDefaultName())
        {
            this->_myNameLabel->setString(gameSaveData.getName());
        }
    }
}

void LeaderboardUILayer::setTaxCoinAmount(int taxCoinAmount)
{
    this->_taxCoinAmountLabel->setString(CommonUtility::convertToString(taxCoinAmount));
}

void LeaderboardUILayer::setMaxDistance(float maxDistance)
{
    this->_distanceLabel->setString(CommonUtility::convertToString((int)maxDistance));
}

void LeaderboardUILayer::shareButtonClicked(cocos2d::Ref *sender)
{
    SocialManager::getInstance()->shareMessageToWeChat("我爱冲上云霄！！！！！");
}

void LeaderboardUILayer::okButtonClicked(cocos2d::Ref *sender)
{
    this->homeButtonClicked(sender);
}

void LeaderboardUILayer::homeButtonClicked(cocos2d::Ref *sender)
{
    NetworkManager::getInstance()->cancelRequest(this->_requestIndex);

    Director::getInstance()->popScene();
}

void LeaderboardUILayer::drawButtonClicked(cocos2d::Ref *sender)
{
    this->addChild(JoinLotteryUILayer::create());
}

void LeaderboardUILayer::leaderboardRequested(void *resultData)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();

    this->_loadingSprite->setVisible(false);

    LeaderboardRecordVector* recordVector = static_cast<LeaderboardRecordVector*>(resultData);
    
    auto leaderboardListView = static_cast<ListView*>(UIHelper::seekNodeByName(this, "leaderboardListView"));
    leaderboardListView->setClippingEnabled(true);
    leaderboardListView->setClippingType(Layout::ClippingType::SCISSOR);

    for (int i = 0; i < recordVector->size(); ++i)
    {
        static const Size contentSize = Size(leaderboardListView->getContentSize().width, 72.0f);
        
        LeaderboardRecord* record = recordVector->at(i);

        if (50 == i)
        {
            Layout* blankLayout = Layout::create();
            blankLayout->setContentSize(contentSize);
            LayerColor* blankLayerColor = LayerColor::create(Color4B(22, 138, 221, 255));
            blankLayerColor->setContentSize(contentSize);
            blankLayout->addChild(blankLayerColor);
            
            Text* pointLabel = Text::create();
            blankLayout->addChild(pointLabel);
            pointLabel->setString("- - - - - - - - - - - - - - - - - - - - - - - - - - -");
            pointLabel->setPosition(contentSize / 2.0f);
            pointLabel->setFontSize(30);
            
            leaderboardListView->addChild(blankLayout);

            ++i;
        }
        
        Layout* itemLayout = Layout::create();
        itemLayout->setContentSize(contentSize);

        LayerColor* layerColor = nullptr;
        if (i % 2 == 0)
        {
            layerColor = LayerColor::create(Color4B(22, 138, 221, 255));
        }
        else
        {
            layerColor = LayerColor::create(Color4B(72, 204, 252, 255));
        }
        layerColor->setContentSize(contentSize);
        itemLayout->addChild(layerColor);

        auto leaderboardUICell = CSLoader::createNode("LeaderboardUICell.csb");
        leaderboardUICell->setPosition(contentSize / 2.0f);
        itemLayout->addChild(leaderboardUICell);

        auto placeLabel = static_cast<Text*>(UIHelper::seekNodeByName(leaderboardUICell, "placeLabel"));
        auto nameLabel = static_cast<Text*>(UIHelper::seekNodeByName(leaderboardUICell, "nameLabel"));
        auto scoreLabel = static_cast<Text*>(UIHelper::seekNodeByName(leaderboardUICell, "scoreLabel"));

        placeLabel->setString(CommonUtility::convertToString(record->getPlace()));
        nameLabel->setString(record->getName());
        scoreLabel->setString(CommonUtility::convertToString(record->getScore()));
        
        leaderboardListView->addChild(itemLayout);
        
        if (record->getID() == gameSaveData.getLeaderboardID())
        {
            this->_myNameLabel = nameLabel;
            this->_myNameLabel->retain();
            this->_myNameLabel->setTextColor(Color4B::YELLOW);
        }
    }
    
    leaderboardListView->refreshView();
}
