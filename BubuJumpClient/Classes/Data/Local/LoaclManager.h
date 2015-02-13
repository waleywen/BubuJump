#ifndef _LoaclManager_H_
#define _LoaclManager_H_

#include "cocos2d.h"

class GameSaveData : public cocos2d::Ref
{
public:
    GameSaveData() : _id(-1), _name(), _totalCoinAmount(0), _maxTaxCoinAmount(0), _maxDistance(0) {};
    
    CC_SYNTHESIZE(int, _id, ID);
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _totalCoinAmount, TotalCoinAmount);
    CC_SYNTHESIZE(int, _maxTaxCoinAmount, MaxTaxCoinAmount);
    CC_SYNTHESIZE(int, _maxDistance, MaxDistance);
};

class LoaclManager
{
public:
    static LoaclManager* getInstance();
    
    LoaclManager();
    
    GameSaveData& getGameSaveData() {return _data;};
    void save();
private:
    GameSaveData _data;
};

#endif // _LoaclManager_H_
