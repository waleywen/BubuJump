#ifndef _LoaclManager_H_
#define _LoaclManager_H_

#include "cocos2d.h"

class GameConfigData
{
    CC_SYNTHESIZE(float, _maxVerticalSpeed, MaxVerticalSpeed);
    CC_SYNTHESIZE(float, _maxHorizontalSpeed, MaxHorizontalSpeed);
    CC_SYNTHESIZE(float, _normalAcceleration, NormalAcceleration);
};

class GameSaveData
{
public:
    GameSaveData() : _leaderboardID(-1), _lotteryID(-1), _name(), _phone(), _totalCoinAmount(0), _maxTaxCoinAmount(0), _maxDistance(0), _needShowJoinLotteryUI(true), _soundEnabled(true), _musicEnabled(true) {};
    bool isDefaultName();
    
    CC_SYNTHESIZE(int, _leaderboardID, LeaderboardID);
    CC_SYNTHESIZE(int, _lotteryID, LotteryID);
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(std::string, _phone, Phone);
    CC_SYNTHESIZE(int, _totalCoinAmount, TotalCoinAmount);
    CC_SYNTHESIZE(int, _maxTaxCoinAmount, MaxTaxCoinAmount);
    CC_SYNTHESIZE(int, _maxDistance, MaxDistance);
    CC_SYNTHESIZE(bool, _needShowJoinLotteryUI, NeedShowJoinLotteryUI);
    CC_SYNTHESIZE(bool, _soundEnabled, SoundEnabled);
    CC_SYNTHESIZE(bool, _musicEnabled, MusicEnabled);
};

class LoaclManager
{
public:
    static LoaclManager* getInstance();
    
    LoaclManager();
    
    inline GameConfigData& getGameConfigData() { return _configData; };
    inline GameSaveData& getGameSaveData() { return _saveData; };
    void save();
private:
    GameConfigData _configData;
    GameSaveData _saveData;
};

#endif // _LoaclManager_H_
