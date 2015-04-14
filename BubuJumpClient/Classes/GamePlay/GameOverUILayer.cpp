#include "GameOverUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "../UIHelper.h"
#include "../CommonUtility.h"
#include "../JoinLotteryUILayer.h"
#include "../Data/Network/NetworkManager.h"
#include "../Data/Local/LoaclManager.h"
#include "../Social/SocialManager.h"

#include "GamePlayScene.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

GameOverUILayer::~GameOverUILayer()
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

bool GameOverUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("GameOverUI.csb");
    this->addChild(uiNode);
    
    this->_taxCoinAmountLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "taxCoinAmountLabel"));
    this->_taxCoinAmountLabel->retain();
    this->_distanceLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "distanceLabel"));
    this->_distanceLabel->retain();

    auto shareButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "shareButton"));
    shareButton->addClickEventListener(CC_CALLBACK_1(GameOverUILayer::shareButtonClicked, this));
    auto retryButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "retryButton"));
    retryButton->addClickEventListener(CC_CALLBACK_1(GameOverUILayer::retryButtonClicked, this));
    auto homeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "homeButton"));
    homeButton->addClickEventListener(CC_CALLBACK_1(GameOverUILayer::homeButtonClicked, this));

    this->_loadingSprite = Sprite::create("loading.png");
    this->_loadingSprite->retain();
    this->_loadingSprite->setPosition(Vec2(360.0f, 400.0f));
    auto sequenceAction = Sequence::create(RotateTo::create(2, 180), RotateTo::create(2, 360), NULL);
    this->_loadingSprite->runAction(Repeat::create(sequenceAction, pow(2,30)));
    this->addChild(this->_loadingSprite);
    
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    if (true == gameSaveData.getNeedShowJoinLotteryUI())
    {
        this->addChild(JoinLotteryUILayer::create());
        
        this->scheduleUpdate();
    }
    
    return true;
}

void GameOverUILayer::update(float delta)
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

void GameOverUILayer::setTaxCoinAmount(int taxCoinAmount)
{
    this->_taxCoinAmountLabel->setString(CommonUtility::convertToString(taxCoinAmount));
}

void GameOverUILayer::setMaxDistance(float maxDistance)
{
    this->_distanceLabel->setString(CommonUtility::convertToString((int)maxDistance));
    
    this->_requestIndex = NetworkManager::getInstance()->submitScore((int)maxDistance, 3, CC_CALLBACK_1(GameOverUILayer::scoreSubmitted, this));
}

void GameOverUILayer::setTaxCoinMap(const TaxCoinMap &taxCoinMap)
{
    auto taxCoinListView = static_cast<ListView*>(UIHelper::seekNodeByName(this, "taxCoinListView"));
//    taxCoinListView->setClippingEnabled(true);
//    taxCoinListView->setClippingType(Layout::ClippingType::SCISSOR);
    int i = 0;
    for (TaxCoinPair taxCoinPair : taxCoinMap)
    {
        static const Size contentSize = Size(taxCoinListView->getContentSize().width, 70.0f);
        Layout *itemLayout = Layout::create();
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
        
        auto gameOverUICell = CSLoader::createNode("GameOverUICell.csb");
        gameOverUICell->setPosition(contentSize / 2.0f);
        itemLayout->addChild(gameOverUICell);

        auto taxNameLabel = static_cast<Text*>(UIHelper::seekNodeByName(gameOverUICell, "taxNameLabel"));
        auto taxCoinCountLabel = static_cast<Text*>(UIHelper::seekNodeByName(gameOverUICell, "taxCoinCountLabel"));
        auto taxCoinSprite = static_cast<Sprite*>(UIHelper::seekNodeByName(gameOverUICell, "taxCoinSprite"));

        switch (taxCoinPair.first) {
            case IndividualIncomeTaxCoinNodeType:
                taxNameLabel->setString("个人所得税");
                taxCoinSprite->setTexture("IndividualIncomeTaxCoin.png");
                break;
            case UrbanMaintenanceAndConstructionTaxCoinNodeType:
                taxNameLabel->setString("城市维护建设税");
                taxCoinSprite->setTexture("UrbanMaintenanceAndConstructionTaxCoin.png");
                break;
            case BusinessTaxCoinNodeType:
                taxNameLabel->setString("营业税");
                taxCoinSprite->setTexture("BusinessTaxCoin.png");
                break;
            case BusinessIncomeTaxCoinNodeType:
                taxNameLabel->setString("企业所得税");
                taxCoinSprite->setTexture("BusinessIncomeTaxCoin.png");
                break;
            case BuildingTaxCoinNodeType:
                taxNameLabel->setString("房产税");
                taxCoinSprite->setTexture("BuildingTaxCoin.png");
                break;
            case VehicleAndVesselTaxCoinNodeType:
                taxNameLabel->setString("车船税");
                taxCoinSprite->setTexture("VehicleAndVesselTaxCoin.png");
                break;
            case DeedTaxCoinNodeType:
                taxNameLabel->setString("契税");
                taxCoinSprite->setTexture("DeedTaxCoin.png");
                break;
            case StampTaxCoinNodeType:
                taxNameLabel->setString("印花税");
                taxCoinSprite->setTexture("StampTaxCoin.png");
                break;
            case LandValueIncrementTaxCoinNodeType:
                taxNameLabel->setString("土地增值税");
                taxCoinSprite->setTexture("LandValueIncrementTaxCoin.png");
                break;
            case UrbanLandUseTaxCoinNodeType:
                taxNameLabel->setString("城镇土地使用税");
                taxCoinSprite->setTexture("UrbanLandUseTaxCoin.png");
                break;
                
            default:
                break;
        }
        
        taxCoinCountLabel->setString(CommonUtility::convertToString(taxCoinPair.second));
        
        taxCoinListView->addChild(itemLayout);
        
        ++i;
    }
    taxCoinListView->refreshView();
}

void GameOverUILayer::shareButtonClicked(cocos2d::Ref *sender)
{
    std::string imagePath = "share.jpg";
    RenderTexture *renderTexture = RenderTexture::create(designResolutionSize.width, designResolutionSize.height);
    renderTexture->begin();
    Director::getInstance()->getRunningScene()->visit();
    renderTexture->end();
    renderTexture->saveToFile(imagePath, false, CC_CALLBACK_2(GameOverUILayer::captured, this));
}

void GameOverUILayer::retryButtonClicked(cocos2d::Ref *sender)
{
    NetworkManager::getInstance()->cancelRequest(this->_requestIndex);

    Director::getInstance()->popToRootScene();
    auto scene = GamePlayScene::create();
    Director::getInstance()->pushScene(scene);
}

void GameOverUILayer::homeButtonClicked(cocos2d::Ref *sender)
{
    Director::getInstance()->popToRootScene();
}

void GameOverUILayer::scoreSubmitted(void *resultData)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();

    this->_loadingSprite->setVisible(false);
    
    auto leaderboardPlaceLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel1"));
    auto leaderboardPlaceLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel2"));
    auto leaderboardPlaceLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel3"));
    
    auto leaderboardNameLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel1"));
    auto leaderboardNameLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel2"));
    auto leaderboardNameLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel3"));
    
    auto leaderboardScoreLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel1"));
    auto leaderboardScoreLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel2"));
    auto leaderboardScoreLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel3"));
    
    LeaderboardRecordVector* recordVector = static_cast<LeaderboardRecordVector*>(resultData);
    if (recordVector->size() > 0)
    {
        LeaderboardRecord* record = recordVector->at(0);
        leaderboardPlaceLabel1->setString(CommonUtility::convertToString(record->getPlace()));
        leaderboardNameLabel1->setString(record->getName());
        leaderboardScoreLabel1->setString(CommonUtility::convertToString(record->getScore()));
        leaderboardPlaceLabel1->setVisible(true);
        leaderboardNameLabel1->setVisible(true);
        leaderboardScoreLabel1->setVisible(true);
        
        if (record->getID() == gameSaveData.getLeaderboardID())
        {
            this->_myNameLabel = leaderboardNameLabel1;
            this->_myNameLabel->retain();
        }
    }
    if (recordVector->size() > 1)
    {
        LeaderboardRecord* record = recordVector->at(1);
        leaderboardPlaceLabel2->setString(CommonUtility::convertToString(record->getPlace()));
        leaderboardNameLabel2->setString(record->getName());
        leaderboardScoreLabel2->setString(CommonUtility::convertToString(record->getScore()));
        leaderboardPlaceLabel2->setVisible(true);
        leaderboardNameLabel2->setVisible(true);
        leaderboardScoreLabel2->setVisible(true);
        
        if (record->getID() == gameSaveData.getLeaderboardID())
        {
            this->_myNameLabel = leaderboardNameLabel2;
            this->_myNameLabel->retain();
        }
    }
    if (recordVector->size() > 2)
    {
        LeaderboardRecord* record = recordVector->at(2);
        leaderboardPlaceLabel3->setString(CommonUtility::convertToString(record->getPlace()));
        leaderboardNameLabel3->setString(record->getName());
        leaderboardScoreLabel3->setString(CommonUtility::convertToString(record->getScore()));
        leaderboardPlaceLabel3->setVisible(true);
        leaderboardNameLabel3->setVisible(true);
        leaderboardScoreLabel3->setVisible(true);
        
        if (record->getID() == gameSaveData.getLeaderboardID())
        {
            this->_myNameLabel = leaderboardNameLabel3;
            this->_myNameLabel->retain();
        }
    }
    if (nullptr != this->_myNameLabel)
    {
        this->_myNameLabel->setTextColor(Color4B::YELLOW);
    }
}

void GameOverUILayer::captured(cocos2d::RenderTexture *renderTexture, const std::string &imagePath)
{
    SocialManager::getInstance()->sharePhotoToWeChat(imagePath);
}
