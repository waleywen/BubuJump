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
    
    _saveData.setLeaderboardID(userDefault->getIntegerForKey("leaderboardID", -1));
    _saveData.setLotteryID(userDefault->getIntegerForKey("lotteryID", -1));
    _saveData.setName(userDefault->getStringForKey("name", "Username"));
    _saveData.setPhone(userDefault->getStringForKey("phone", ""));
    _saveData.setTotalCoinAmount(userDefault->getIntegerForKey("totalCoinAmount", 0));
    _saveData.setMaxTaxCoinAmount(userDefault->getIntegerForKey("maxTaxCoinAmount", 0));
    _saveData.setMaxDistance(userDefault->getIntegerForKey("maxDistance", 0));
    _saveData.setNeedShowJoinLotteryUI(userDefault->getBoolForKey("needShowJoinLotteryUI", true));
    _saveData.setSoundEnabled(userDefault->getBoolForKey("soundEnabled", true));
    _saveData.setMusicEnabled(userDefault->getBoolForKey("musicEnabled", true));
    
    std::string filePath = "/mnt/sdcard/BubuJump/Config.plist";
    auto sharedFileUtils = FileUtils::getInstance();
    if (true == sharedFileUtils->isFileExist(filePath))
    {
        ValueVector configVector = FileUtils::getInstance()->getValueVectorFromFile(filePath);

        _configData.setMaxVerticalSpeed(configVector.at(0).asInt());
        _configData.setMaxHorizontalSpeed(configVector.at(1).asInt());
        _configData.setNormalAcceleration(configVector.at(2).asInt());
    }
    else
    {
        _configData.setMaxVerticalSpeed(1000);
        _configData.setMaxHorizontalSpeed(30);
        _configData.setNormalAcceleration(-1000);
    }
}

void LoaclManager::save()
{
    UserDefault* userDefault = UserDefault::getInstance();

    userDefault->setIntegerForKey("leaderboardID", _saveData.getLeaderboardID());
    userDefault->setIntegerForKey("lotteryID", _saveData.getLotteryID());
    userDefault->setStringForKey("name", _saveData.getName());
    userDefault->setStringForKey("phone", _saveData.getPhone());
    userDefault->setIntegerForKey("totalCoinAmount", _saveData.getTotalCoinAmount());
    userDefault->setIntegerForKey("maxTaxCoinAmount", _saveData.getMaxTaxCoinAmount());
    userDefault->setIntegerForKey("maxDistance", _saveData.getMaxDistance());
    userDefault->setBoolForKey("needShowJoinLotteryUI", _saveData.getNeedShowJoinLotteryUI());
    userDefault->setBoolForKey("soundEnabled", _saveData.getSoundEnabled());
    userDefault->setBoolForKey("musicEnabled", _saveData.getMusicEnabled());
}
