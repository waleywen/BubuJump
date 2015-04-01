#include "MainMenuUILayer.h"

#include "cocostudio/CocoStudio.h"
#include "audio/include/SimpleAudioEngine.h"

#include "UIHelper.h"

#include "GamePlay/GamePlayScene.h"
#include "LeaderboardUILayer.h"
#include "HelpUILayer.h"
#include "JoinLotteryUILayer.h"
#include "TaxBibleUILayer.h"
#include "SettingUILayer.h"
#include "Social/SocialManager.h"
#include "Data/Network/NetworkManager.h"
#include "Data/Local/LoaclManager.h"

#include "Audio/AudioManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace CocosDenshion;

MainMenuUILayer::~MainMenuUILayer()
{

}

bool MainMenuUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("MainMenuUI.csb");
    this->addChild(uiNode);

    auto playButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "playButton"));
    playButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::playButtonClicked, this));
    auto taxButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "taxButton"));
    taxButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::taxButtonClicked, this));
    auto leaderboardButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "leaderboardButton"));
    leaderboardButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::leaderboardButtonClicked, this));
    auto helpButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "helpButton"));
    helpButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::helpButtonClicked, this));
    auto optionButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "optionButton"));
    optionButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::optionButtonClicked, this));
    auto shareButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "shareButton"));
    shareButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::shareButtonClicked, this));
    auto drawButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "drawButton"));
    drawButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::drawButtonClicked, this));

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    if (gameSaveData.getLotteryID() == -1 && gameSaveData.getPhone().length() > 0)
    {
        NetworkManager::getInstance()->joinLottery();
    }
    
    SimpleAudioEngine::getInstance()->setEffectsVolume(true == gameSaveData.getSoundEnabled() ? 1.0f : 0.0f);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(true == gameSaveData.getMusicEnabled() ? 1.0f : 0.0f);
    
    AudioManager::getInstance()->playBackgroundMusic("music.mp3", true);
    
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-button.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-coin-pickup.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-count-down.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-fly-boot.aac");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-footboard-cloud.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-footboard-move.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-footboard.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-magnet.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-player-die.aac");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-rocket.aac");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-soft-cloud.aac");
    SimpleAudioEngine::getInstance()->preloadEffect("sfx-thorn-footboard.aac");

    return true;
}

void MainMenuUILayer::playButtonClicked(cocos2d::Ref *sender)
{
    auto scene = GamePlayScene::create();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::taxButtonClicked(cocos2d::Ref *sender)
{
    auto scene = TaxBibleUILayer::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::leaderboardButtonClicked(cocos2d::Ref *sender)
{
    auto scene = LeaderboardUILayer::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::helpButtonClicked(cocos2d::Ref *sender)
{
    auto scene = HelpUILayer::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::optionButtonClicked(cocos2d::Ref *sender)
{
    auto scene = SettingUILayer::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::shareButtonClicked(cocos2d::Ref *sender)
{
    SocialManager::getInstance()->shareMessageToWeChat("我爱冲上云霄！！！！！");
}

void MainMenuUILayer::drawButtonClicked(cocos2d::Ref *sender)
{
    this->addChild(JoinLotteryUILayer::create());
}
