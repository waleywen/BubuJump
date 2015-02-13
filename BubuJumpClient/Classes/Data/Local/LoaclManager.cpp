#include "LoaclManager.h"

#include "base/CCUserDefault.h"

USING_NS_CC;

LoaclManager* LoaclManager::getInstance()
{
    static LoaclManager s_instance;
    return &s_instance;
}

LoaclManager::LoaclManager() : _data()
{
    UserDefault* userDefault = UserDefault::getInstance();
    
    _data.setID(userDefault->getIntegerForKey("id", -1));
    _data.setName(userDefault->getStringForKey("name", "Username"));
    _data.setTotalCoinAmount(userDefault->getIntegerForKey("totalCoinAmount", 0));
    _data.setMaxTaxCoinAmount(userDefault->getIntegerForKey("maxTaxCoinAmount", 0));
    _data.setMaxDistance(userDefault->getIntegerForKey("maxDistance", 0));
}

void LoaclManager::save()
{
    UserDefault* userDefault = UserDefault::getInstance();

    userDefault->setIntegerForKey("id", _data.getID());
    userDefault->setStringForKey("name", _data.getName());
    userDefault->setIntegerForKey("totalCoinAmount", _data.getTotalCoinAmount());
    userDefault->setIntegerForKey("maxTaxCoinAmount", _data.getMaxTaxCoinAmount());
    userDefault->setIntegerForKey("maxDistance", _data.getMaxDistance());
}