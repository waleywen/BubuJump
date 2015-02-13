#include "LeaderboardUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "UIHelper.h"
#include "CommonUtility.h"
#include "Data/Network/NetworkManager.h"
#include "Data/Local/LoaclManager.h"

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

    auto okButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "okButton"));
    okButton->addClickEventListener(CC_CALLBACK_1(LeaderboardUILayer::okButtonClicked, this));
    auto homeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "homeButton"));
    homeButton->addClickEventListener(CC_CALLBACK_1(LeaderboardUILayer::homeButtonClicked, this));
    
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    
    if (gameSaveData.getMaxDistance() > 0)
    {
        this->_loadingSprite = Sprite::create("loading.png");
        this->_loadingSprite->retain();
        this->_loadingSprite->setPosition(Vec2(360.0f, 400.0f));
        auto sequenceAction = Sequence::create(RotateTo::create(2, 180), RotateTo::create(2, 360), NULL);
        this->_loadingSprite->runAction(Repeat::create(sequenceAction, pow(2,30)));
        this->addChild(this->_loadingSprite);
        
        this->_requestIndex = NetworkManager::getInstance()->submitScore(gameSaveData.getMaxDistance(), 6, CC_CALLBACK_1(LeaderboardUILayer::scoreSubmitted, this));
    }
    
    this->_taxCoinAmountLabel->setString(CommonUtility::convertToString(gameSaveData.getMaxTaxCoinAmount()));
    this->_distanceLabel->setString(CommonUtility::convertToString(gameSaveData.getMaxDistance()));

    return true;
}

void LeaderboardUILayer::setTaxCoinAmount(int taxCoinAmount)
{
    this->_taxCoinAmountLabel->setString(CommonUtility::convertToString(taxCoinAmount));
}

void LeaderboardUILayer::setMaxDistance(float maxDistance)
{
    this->_distanceLabel->setString(CommonUtility::convertToString((int)maxDistance));
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

void LeaderboardUILayer::scoreSubmitted(void *resultData)
{
    this->_loadingSprite->setVisible(false);
    
    auto leaderboardPlaceLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel1"));
    auto leaderboardPlaceLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel2"));
    auto leaderboardPlaceLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel3"));
    auto leaderboardPlaceLabel4 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel4"));
    auto leaderboardPlaceLabel5 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel5"));
    auto leaderboardPlaceLabel6 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardPlaceLabel6"));
    
    auto leaderboardNameLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel1"));
    auto leaderboardNameLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel2"));
    auto leaderboardNameLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel3"));
    auto leaderboardNameLabel4 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel4"));
    auto leaderboardNameLabel5 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel5"));
    auto leaderboardNameLabel6 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardNameLabel6"));
    
    auto leaderboardScoreLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel1"));
    auto leaderboardScoreLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel2"));
    auto leaderboardScoreLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel3"));
    auto leaderboardScoreLabel4 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel4"));
    auto leaderboardScoreLabel5 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel5"));
    auto leaderboardScoreLabel6 = static_cast<Text*>(UIHelper::seekNodeByName(this, "leaderboardScoreLabel6"));
    
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
    }
    if (recordVector->size() > 3)
    {
        LeaderboardRecord* record = recordVector->at(3);
        leaderboardPlaceLabel4->setString(CommonUtility::convertToString(record->getPlace()));
        leaderboardNameLabel4->setString(record->getName());
        leaderboardScoreLabel4->setString(CommonUtility::convertToString(record->getScore()));
        leaderboardPlaceLabel4->setVisible(true);
        leaderboardNameLabel4->setVisible(true);
        leaderboardScoreLabel4->setVisible(true);
    }
    if (recordVector->size() > 4)
    {
        LeaderboardRecord* record = recordVector->at(4);
        leaderboardPlaceLabel5->setString(CommonUtility::convertToString(record->getPlace()));
        leaderboardNameLabel5->setString(record->getName());
        leaderboardScoreLabel5->setString(CommonUtility::convertToString(record->getScore()));
        leaderboardPlaceLabel5->setVisible(true);
        leaderboardNameLabel5->setVisible(true);
        leaderboardScoreLabel5->setVisible(true);
    }
    if (recordVector->size() > 5)
    {
        LeaderboardRecord* record = recordVector->at(5);
        leaderboardPlaceLabel6->setString(CommonUtility::convertToString(record->getPlace()));
        leaderboardNameLabel6->setString(record->getName());
        leaderboardScoreLabel6->setString(CommonUtility::convertToString(record->getScore()));
        leaderboardPlaceLabel6->setVisible(true);
        leaderboardNameLabel6->setVisible(true);
        leaderboardScoreLabel6->setVisible(true);
    }
}
