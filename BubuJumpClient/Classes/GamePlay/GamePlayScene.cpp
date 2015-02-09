#include "GamePlayScene.h"

#include "GamePlayLayer.h"
#include "GamePlayUILayer.h"
#include "GameLeaderboardUI.h"
#include "../Data/Local/LoaclManager.h"

USING_NS_CC;

GamePlayScene::~GamePlayScene()
{
    if (nullptr != this->_gamePlayLayer)
    {
        this->_gamePlayLayer->release();
        this->_gamePlayLayer = nullptr;
    }
    if (nullptr != this->_gamePlayUILayer)
    {
        this->_gamePlayUILayer->release();
        this->_gamePlayUILayer = nullptr;
    }
}

bool GamePlayScene::init()
{
    if(false == Scene::init())
    {
        return false;
    }
    
    this->_gamePlayLayer = GamePlayLayer::create();
    this->_gamePlayLayer->retain();
    this->addChild(this->_gamePlayLayer);

    this->_gamePlayUILayer = GamePlayUILayer::create();
    this->_gamePlayUILayer->retain();
    this->addChild(this->_gamePlayUILayer);

    this->scheduleUpdate();

    return true;
}

void GamePlayScene::update(float delta)
{
    this->_gamePlayLayer->gameUpdate(delta);
    
    this->_gamePlayUILayer->setHeartCount(this->_gamePlayLayer->getHeartCount());
    this->_gamePlayUILayer->setCoinAmount(this->_gamePlayLayer->getCoinAmount());
    this->_gamePlayUILayer->setMaxDistance(this->_gamePlayLayer->getMaxDistance());
    this->_gamePlayUILayer->setEffect(this->_gamePlayLayer->getEffect());
    
    this->_gamePlayUILayer->gameUpdate(delta);
    
    if (true == this->_gamePlayLayer->getDead())
    {
        GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
        if (this->_gamePlayLayer->getCoinAmount() > gameSaveData.getMaxCoinCount())
        {
            gameSaveData.setMaxCoinCount(this->_gamePlayLayer->getCoinAmount());
        }
        if (this->_gamePlayLayer->getMaxDistance() > gameSaveData.getMaxDistance())
        {
            gameSaveData.setMaxDistance(this->_gamePlayLayer->getMaxDistance());
        }
        LoaclManager::getInstance()->save();
        
        auto gamePauseUILayer = GameLeaderboardUI::create();
        gamePauseUILayer->setCoinAmount(this->_gamePlayLayer->getCoinAmount());
        gamePauseUILayer->setMaxDistance(this->_gamePlayLayer->getMaxDistance());
        
        auto scene = Scene::create();
        scene->addChild(gamePauseUILayer);

        Director::getInstance()->replaceScene(scene);
    }
}
