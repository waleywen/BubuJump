#ifndef _LoaclManager_H_
#define _LoaclManager_H_

#include "cocos2d.h"

class GameSaveData : public cocos2d::Ref
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
    
    GameSaveData& getGameSaveData() {return _data;};
    void save();
private:
    GameSaveData _data;
};

#endif // _LoaclManager_H_
