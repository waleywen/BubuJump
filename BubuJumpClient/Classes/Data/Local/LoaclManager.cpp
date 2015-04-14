#include "LoaclManager.h"

#include "base/CCUserDefault.h"

USING_NS_CC;

bool GameSaveData::isDefaultName()
{
    return this->_name == "Username";
}

LoaclManager* LoaclManager::getInstance()
{
    static LoaclManager s_instance;
    return &s_instance;
}

LoaclManager::LoaclManager() : _configData(), _saveData()
{
    UserDefault* userDefault = UserDefault::getInstance();
    
//    if (userDefault->getIntegerForKey("Version", -1) != 1)
//    {
//        this->save();
//        userDefault->setIntegerForKey("Version", 1);
//    }
    
    _saveData.setLeaderboardID(userDefault->getIntegerForKey("leaderboardID", _saveData.getLeaderboardID()));
    _saveData.setLotteryID(userDefault->getIntegerForKey("lotteryID", _saveData.getLotteryID()));
    _saveData.setLotteryInfoSynchronized(userDefault->getBoolForKey("lotteryInfoSynchronized", _saveData.getLotteryInfoSynchronized()));
    _saveData.setName(userDefault->getStringForKey("name", _saveData.getName()));
    _saveData.setPhone(userDefault->getStringForKey("phone", _saveData.getPhone()));
    _saveData.setTotalCoinAmount(userDefault->getIntegerForKey("totalCoinAmount", _saveData.getTotalCoinAmount()));
    _saveData.setMaxTaxCoinAmount(userDefault->getIntegerForKey("maxTaxCoinAmount", _saveData.getMaxTaxCoinAmount()));
    _saveData.setMaxDistance(userDefault->getIntegerForKey("maxDistance", _saveData.getMaxDistance()));
    _saveData.setNeedShowJoinLotteryUI(userDefault->getBoolForKey("needShowJoinLotteryUI", _saveData.getNeedShowJoinLotteryUI()));
    _saveData.setSoundEnabled(userDefault->getBoolForKey("soundEnabled", _saveData.getSoundEnabled()));
    _saveData.setMusicEnabled(userDefault->getBoolForKey("musicEnabled", _saveData.getMusicEnabled()));
    
//    std::string filePath = "/mnt/sdcard/BubuJump/Config.plist";
//    auto sharedFileUtils = FileUtils::getInstance();
//    if (true == sharedFileUtils->isFileExist(filePath))
//    {
//        ValueVector configVector = FileUtils::getInstance()->getValueVectorFromFile(filePath);
//
//        _configData.setMaxVerticalSpeed(configVector.at(0).asInt());
//        _configData.setMaxHorizontalSpeed(configVector.at(1).asInt());
//        _configData.setNormalAcceleration(configVector.at(2).asInt());
//    }
//    else
    {
        _configData.setMaxVerticalSpeed(1500);
        _configData.setMaxHorizontalSpeed(70);
        _configData.setNormalAcceleration(-2000);
    }
}

void LoaclManager::save()
{
    UserDefault* userDefault = UserDefault::getInstance();

    userDefault->setIntegerForKey("leaderboardID", _saveData.getLeaderboardID());
    userDefault->setIntegerForKey("lotteryID", _saveData.getLotteryID());
    userDefault->setBoolForKey("lotteryInfoSynchronized", _saveData.getLotteryInfoSynchronized());
    userDefault->setStringForKey("name", _saveData.getName());
    userDefault->setStringForKey("phone", _saveData.getPhone());
    userDefault->setIntegerForKey("totalCoinAmount", _saveData.getTotalCoinAmount());
    userDefault->setIntegerForKey("maxTaxCoinAmount", _saveData.getMaxTaxCoinAmount());
    userDefault->setIntegerForKey("maxDistance", _saveData.getMaxDistance());
    userDefault->setBoolForKey("needShowJoinLotteryUI", _saveData.getNeedShowJoinLotteryUI());
    userDefault->setBoolForKey("soundEnabled", _saveData.getSoundEnabled());
    userDefault->setBoolForKey("musicEnabled", _saveData.getMusicEnabled());
}
