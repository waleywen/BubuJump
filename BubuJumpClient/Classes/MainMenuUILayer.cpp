#include "MainMenuUILayer.h"

#include "cocostudio/CocoStudio.h"
#include "audio/include/SimpleAudioEngine.h"

#include "UIHelper.h"

#include "GamePlay/GamePlayScene.h"
#include "LeaderboardUILayer.h"

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
    auto optionButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "optionButton"));
    optionButton->addClickEventListener(CC_CALLBACK_1(MainMenuUILayer::optionButtonClicked, this));

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music.mp3");
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);

    return true;
}

void MainMenuUILayer::playButtonClicked(cocos2d::Ref *sender)
{
    auto scene = GamePlayScene::create();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::taxButtonClicked(cocos2d::Ref *sender)
{
    
}

void MainMenuUILayer::leaderboardButtonClicked(cocos2d::Ref *sender)
{
    auto scene = LeaderboardUILayer::createScene();
    Director::getInstance()->pushScene(scene);
}

void MainMenuUILayer::optionButtonClicked(cocos2d::Ref *sender)
{
    
}
