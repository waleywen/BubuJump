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

LoaclManager::LoaclManager() : _data()
{
    UserDefault* userDefault = UserDefault::getInstance();
    
    _data.setLeaderboardID(userDefault->getIntegerForKey("leaderboardID", -1));
    _data.setLotteryID(userDefault->getIntegerForKey("lotteryID", -1));
    _data.setName(userDefault->getStringForKey("name", "Username"));
    _data.setPhone(userDefault->getStringForKey("phone", ""));
    _data.setTotalCoinAmount(userDefault->getIntegerForKey("totalCoinAmount", 0));
    _data.setMaxTaxCoinAmount(userDefault->getIntegerForKey("maxTaxCoinAmount", 0));
    _data.setMaxDistance(userDefault->getIntegerForKey("maxDistance", 0));
    _data.setNeedShowJoinLotteryUI(userDefault->getBoolForKey("needShowJoinLotteryUI", true));
}

void LoaclManager::save()
{
    UserDefault* userDefault = UserDefault::getInstance();

    userDefault->setIntegerForKey("leaderboardID", _data.getLeaderboardID());
    userDefault->setIntegerForKey("lotteryID", _data.getLotteryID());
    userDefault->setStringForKey("name", _data.getName());
    userDefault->setStringForKey("phone", _data.getPhone());
    userDefault->setIntegerForKey("totalCoinAmount", _data.getTotalCoinAmount());
    userDefault->setIntegerForKey("maxTaxCoinAmount", _data.getMaxTaxCoinAmount());
    userDefault->setIntegerForKey("maxDistance", _data.getMaxDistance());
    userDefault->setBoolForKey("needShowJoinLotteryUI", _data.getNeedShowJoinLotteryUI());
}