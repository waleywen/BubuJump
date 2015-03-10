#include "SettingUILayer.h"

#include "cocostudio/CocoStudio.h"
#include "audio/include/SimpleAudioEngine.h"

#include "UIHelper.h"

#include "Data/Local/LoaclManager.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace CocosDenshion;

SettingUILayer::~SettingUILayer()
{

}

bool SettingUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("SettingUI.csb");
    this->addChild(uiNode);

    auto backButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "backButton"));
    backButton->addClickEventListener(CC_CALLBACK_1(SettingUILayer::backButtonClicked, this));
    auto soundButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "soundButton"));
    soundButton->addClickEventListener(CC_CALLBACK_1(SettingUILayer::soundButtonClicked, this));
    auto musicButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "musicButton"));
    musicButton->addClickEventListener(CC_CALLBACK_1(SettingUILayer::musicButtonClicked, this));

    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    soundButton->loadTextureNormal(true == gameSaveData.getSoundEnabled() ? "SettingUITurnOnButton.png" : "SettingUITurnOffButton.png");
    musicButton->loadTextureNormal(true == gameSaveData.getMusicEnabled() ? "SettingUITurnOnButton.png" : "SettingUITurnOffButton.png");
    
    return true;
}

void SettingUILayer::backButtonClicked(cocos2d::Ref *sender)
{
    Director::getInstance()->popScene();
}

void SettingUILayer::soundButtonClicked(cocos2d::Ref *sender)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    gameSaveData.setSoundEnabled(!gameSaveData.getSoundEnabled());
    LoaclManager::getInstance()->save();
    
    SimpleAudioEngine::getInstance()->setEffectsVolume(true == gameSaveData.getSoundEnabled() ? 1.0f : 0.0f);
    
    auto soundButton = static_cast<Button*>(sender);
    soundButton->loadTextureNormal(true == gameSaveData.getSoundEnabled() ? "SettingUITurnOnButton.png" : "SettingUITurnOffButton.png");
}

void SettingUILayer::musicButtonClicked(cocos2d::Ref *sender)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    gameSaveData.setMusicEnabled(!gameSaveData.getMusicEnabled());
    LoaclManager::getInstance()->save();

    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(true == gameSaveData.getMusicEnabled() ? 1.0f : 0.0f);
    
    auto musicButton = static_cast<Button*>(sender);
    musicButton->loadTextureNormal(true == gameSaveData.getMusicEnabled() ? "SettingUITurnOnButton.png" : "SettingUITurnOffButton.png");
}
