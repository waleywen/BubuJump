#ifndef _NetworkManager_H_
#define _NetworkManager_H_

#include "cocos2d.h"
#include "network/HttpClient.h"

class LeaderboardRecord : public cocos2d::Ref
{
public:
    LeaderboardRecord() : _id(0), _name(), _score(0) {};
    virtual ~LeaderboardRecord() {};

    bool init();

    CREATE_FUNC(LeaderboardRecord);

    CC_SYNTHESIZE(int, _id, ID);
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _score, Score);
    CC_SYNTHESIZE(int, _place, Place);
};

typedef typename cocos2d::Vector<LeaderboardRecord*> LeaderboardRecordVector;
typedef typename cocos2d::Vector<LeaderboardRecord*>::iterator LeaderboardRecordVectorIterator;

typedef typename std::function<void(void*)> NetworkCallback;

class NetworkManager
{
public:
    static NetworkManager* getInstance();
    
    NetworkManager() : _nextIndex(0) {};
    
    void cancelRequest(int requestIndex);
    int requestLeaderboard(NetworkCallback callback);
    int submitScore(int score, int resultSize, NetworkCallback callback);
    void joinLottery();
private:
    struct NetworkCallbackObject
    {
        int index;
        NetworkCallback callback;
        bool canceled;
    };

    NetworkManager::NetworkCallbackObject& generateCallbackObject(NetworkCallback callback);
    
    void leaderboardRequested(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

    void scoreSubmitted3(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void scoreSubmitted6(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void scoreSubmitted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response, int resultSize);
    
    void lotteryJoined(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
    typedef typename std::map<int, NetworkCallbackObject> NetworkCallbackMap;
    typedef typename std::pair<int, NetworkCallbackObject> NetworkCallbackPair;
    typedef typename std::map<int, NetworkCallbackObject>::iterator NetworkCallbackMapIterator;
    NetworkCallbackMap _callbackMap;
    
    int _nextIndex;
};

#endif // _NetworkManager_H_
