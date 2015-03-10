#include "NetworkManager.h"

#include "json/rapidjson.h"
#include "json/document.h"

#include "../../CommonUtility.h"
#include "../md5.h"
#include "../Local/LoaclManager.h"

USING_NS_CC;
using namespace cocos2d::network;

//const std::string SERVER_ADDRESS = "http://localhost/";
//const std::string SERVER_ADDRESS = "http://192.168.31.217/";
//const std::string SERVER_ADDRESS = "http://bubujump.sinaapp.com/";
const std::string SERVER_ADDRESS = "http://touchthesky.sinaapp.com/";
const std::string MD5_KEY = "1234567890";

std::string md5SumString(const std::string& type, const std::string& id, const std::string& name, const std::string& score)
{
    std::string originalString = MD5_KEY + type + id + name + score;
    MD5 md5(originalString);
    return md5.md5();
}

bool LeaderboardRecord::init()
{
    return true;
}

NetworkManager* NetworkManager::getInstance()
{
    static NetworkManager s_instance;
    return &s_instance;
}

void NetworkManager::cancelRequest(int requestIndex)
{
    NetworkCallbackMapIterator iter = this->_callbackMap.find(requestIndex);
    if (iter != this->_callbackMap.end())
    {
        (*iter).second.canceled = true;
    }
}

int NetworkManager::requestLeaderboard(NetworkCallback callback)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    
    std::string idString = "";
    if (-1 != gameSaveData.getLeaderboardID())
    {
        idString = CommonUtility::convertToString(gameSaveData.getLeaderboardID());
    }
    
    std::string url = SERVER_ADDRESS + "leaderboard.php";
    url += "?type=0";
    if (-1 != gameSaveData.getLeaderboardID())
    {
        url += "&id=";
        url += idString;
    }
    url += "&sum=";
    
    url += md5SumString("0", idString, "", "");
    
    NetworkCallbackObject& callbackObject = this->generateCallbackObject(callback);
    
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(NetworkManager::leaderboardRequested, this));
    request->setTag("requestLeaderboard");
    request->setUserData(&callbackObject);
    HttpClient::getInstance()->send(request);
    request->release();
    
    return callbackObject.index;
}

int NetworkManager::submitScore(int score, int resultSize, NetworkCallback callback)
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();

    std::string scoreString = CommonUtility::convertToString(score);
    
    std::string idString = "";
    if (-1 != gameSaveData.getLeaderboardID())
    {
        idString = CommonUtility::convertToString(gameSaveData.getLeaderboardID());
    }
    
    std::string nameString = gameSaveData.getName();
    
    std::string url = SERVER_ADDRESS + "leaderboard.php";
    url += "?type=1";
    if (-1 != gameSaveData.getLeaderboardID())
    {
        url += "&id=";
        url += idString;
    }
    url += "&name=";
    url += nameString;
    url += "&score=";
    url += scoreString;
    url += "&sum=";
    
    url += md5SumString("1", idString, nameString, scoreString);
    
    NetworkCallbackObject& callbackObject = this->generateCallbackObject(callback);
    
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    if (3 == resultSize)
    {
        request->setResponseCallback(CC_CALLBACK_2(NetworkManager::scoreSubmitted3, this));
    }
    else if (6 == resultSize)
    {
        request->setResponseCallback(CC_CALLBACK_2(NetworkManager::scoreSubmitted6, this));
    }
    request->setTag("submitScore");
    request->setUserData(&callbackObject);
    HttpClient::getInstance()->send(request);
    request->release();
    
    return callbackObject.index;
}

void NetworkManager::joinLottery()
{
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    
    if (0 >= gameSaveData.getPhone().length())
    {
        return;
    }
    
    std::string idString = "";
    if (-1 != gameSaveData.getLotteryID())
    {
        idString = CommonUtility::convertToString(gameSaveData.getLotteryID());
    }
    
    std::string nameString = gameSaveData.getName();
    std::string phoneString = gameSaveData.getPhone();

    std::string url = SERVER_ADDRESS + "lottery.php";
    url += "?name=";
    url += nameString;
    url += "&phone=";
    url += phoneString;
    if (-1 != gameSaveData.getLotteryID())
    {
        url += "&id=";
        url += idString;
    }
    url += "&sum=";
    url += md5SumString("", idString, nameString, phoneString);
    
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(NetworkManager::lotteryJoined, this));
    request->setTag("syncMyInfo");
    HttpClient::getInstance()->send(request);
    request->release();
}

NetworkManager::NetworkCallbackObject& NetworkManager::generateCallbackObject(NetworkCallback callback)
{
    int index = (++_nextIndex);
    NetworkCallbackObject& callbackObject = this->_callbackMap.insert(NetworkCallbackPair(index, {index, callback, false})).first->second;
    return callbackObject;
}

void NetworkManager::errorReturnMyRecord(NetworkManager::NetworkCallbackObject *callbackObject)
{
    if (nullptr != callbackObject && false == callbackObject->canceled)
    {
        LeaderboardRecordVector resultRecordVector;
        
        GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();

        LeaderboardRecord* record = LeaderboardRecord::create();
        record->setID(gameSaveData.getLeaderboardID());
        if (false == gameSaveData.isDefaultName())
        {
            record->setName(gameSaveData.getName());
        }
        else
        {
            record->setName("我");
        }
        record->setScore(gameSaveData.getMaxDistance());
        record->setPlace(1);
        resultRecordVector.pushBack(record);

        callbackObject->callback(&resultRecordVector);
    }
}

void NetworkManager::leaderboardRequested(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    NetworkCallbackObject* callbackObject = static_cast<NetworkCallbackObject*>(response->getHttpRequest()->getUserData());
    if (true == callbackObject->canceled)
    {
        return;
    }
    
    if (!response)
    {
        this->errorReturnMyRecord(callbackObject);
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }
    int statusCode = (int)response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("%s", statusString);
    log("response code: %d", statusCode);
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        this->errorReturnMyRecord(callbackObject);
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string json = "";
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        json += (*buffer)[i];
    }
    
    log("%s", json.c_str());
    
    rapidjson::Document document;
    document.Parse<0>(json.c_str());
    
    LeaderboardRecordVector resultRecordVector;
    
    int sameScorePlace = document["sameScorePlace"].GetInt();
    int myID = document["myID"].GetInt();
    int myScore = document["myScore"].GetInt();
    
    bool isTop50Player = false;
    
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    std::string myName = "";
    if (false == gameSaveData.isDefaultName())
    {
        myName = gameSaveData.getName();
    }
    else
    {
        myName = "我";
    }

    
    rapidjson::Value& leaderboardArray = document["leaderboard"];
    for(int i = 0; i < leaderboardArray.Capacity(); ++i)
    {
        rapidjson::Value &recordJson = leaderboardArray[i];
        
        LeaderboardRecord* record = LeaderboardRecord::create();
        record->setID(recordJson["id"].GetInt());
        record->setName(recordJson["name"].GetString());
        record->setScore(recordJson["score"].GetInt());
        record->setPlace(i + 1);
        
        resultRecordVector.pushBack(record);
        
        if (record->getID() == myID)
        {
            isTop50Player = true;
            record->setName(myName);
        }
    }
    
    if (false == isTop50Player && -1 != myID)
    {
        LeaderboardRecord* record = LeaderboardRecord::create();
        record->setID(myID);
        record->setName(myName);
        record->setScore(myScore);

        if (50 >= sameScorePlace)
        {
            record->setPlace(51);
        }
        else
        {
            record->setPlace(sameScorePlace);
        }
        
        resultRecordVector.pushBack(record);
    }
    
    if (false == callbackObject->canceled)
    {
        callbackObject->callback(&resultRecordVector);
    }
}

void NetworkManager::scoreSubmitted3(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    this->scoreSubmitted(sender, response, 3);
}

void NetworkManager::scoreSubmitted6(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    this->scoreSubmitted(sender, response, 6);
}

void NetworkManager::scoreSubmitted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response, int resultSize)
{
    NetworkCallbackObject* callbackObject = static_cast<NetworkCallbackObject*>(response->getHttpRequest()->getUserData());
    if (true == callbackObject->canceled)
    {
        return;
    }
    
    if (!response)
    {
        this->errorReturnMyRecord(callbackObject);
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }
    int statusCode = (int)response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("%s", statusString);
    log("response code: %d", statusCode);
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        this->errorReturnMyRecord(callbackObject);
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string json = "";
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        json += (*buffer)[i];
    }
    
    log("%s", json.c_str());
    
    rapidjson::Document document;
    document.Parse<0>(json.c_str());

    LeaderboardRecordVector recordVector;
    
    int sameScorePlace = document["sameScorePlace"].GetInt();
    int myID = document["myID"].GetInt();
    int myScore = document["myScore"].GetInt();
    
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    gameSaveData.setLeaderboardID(myID);
    LoaclManager::getInstance()->save();
    
    bool foundMyScore = false;
    int startPlace = sameScorePlace;
    LeaderboardRecord* myRecord = nullptr;
    
    rapidjson::Value& leaderboardArray = document["leaderboard"];
    for(int i = 0; i < leaderboardArray.Capacity(); ++i)
    {
        rapidjson::Value &recordJson = leaderboardArray[i];

        LeaderboardRecord* record = LeaderboardRecord::create();
        record->setID(recordJson["id"].GetInt());
        record->setName(recordJson["name"].GetString());
        record->setScore(recordJson["score"].GetInt());
        
        recordVector.pushBack(record);
        
        if (record->getID() == myID)
        {
            myRecord = record;
        }
        
        if (record->getScore() == myScore)
        {
            foundMyScore = true;
        }
        if (false == foundMyScore)
        {
            --startPlace;
        }
    }
    
    for (LeaderboardRecord* theRecord : recordVector)
    {
        theRecord->setPlace(startPlace++);
    }
    
    if (false == gameSaveData.isDefaultName())
    {
        myRecord->setName(gameSaveData.getName());
    }
    else
    {
        myRecord->setName("我");
    }

    LeaderboardRecordVector resultRecordVector;
    if (leaderboardArray.Size() <= resultSize)
    {
        resultRecordVector = recordVector;
    }
    else
    {
        resultRecordVector.pushBack(myRecord);
        LeaderboardRecordVectorIterator iter = recordVector.find(myRecord);
        bool hasPrevious = true;
        bool hasNext = true;
        if (recordVector.begin() == iter)
        {
            hasPrevious = false;
        }
        for (int i = 1; resultRecordVector.size() < resultSize; ++i)
        {
            LeaderboardRecordVectorIterator previousIter = iter - i;
            if (true == hasPrevious)
            {
                resultRecordVector.insert(0, *previousIter);
                if (recordVector.begin() == previousIter)
                {
                    hasPrevious = false;
                }
            }
            LeaderboardRecordVectorIterator nextIter = iter + i;
            if (true == hasNext)
            {
                if (recordVector.end() != nextIter)
                {
                    resultRecordVector.pushBack(*nextIter);
                }
                else
                {
                    hasNext = false;
                }
            }
        }
    }
    
    if (false == callbackObject->canceled)
    {
        callbackObject->callback(&resultRecordVector);
    }
}

void NetworkManager::lotteryJoined(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }
    int statusCode = (int)response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("%s", statusString);
    log("response code: %d", statusCode);
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string json = "";
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        json += (*buffer)[i];
    }
    
    log("%s", json.c_str());
    
    rapidjson::Document document;
    document.Parse<0>(json.c_str());
    
    int myID = document["myID"].GetInt();
    std::string name = document["name"].GetString();
    std::string phone = document["phone"].GetString();
    
    GameSaveData& gameSaveData = LoaclManager::getInstance()->getGameSaveData();
    gameSaveData.setLotteryID(myID);
    gameSaveData.setName(name);
    gameSaveData.setPhone(phone);
    LoaclManager::getInstance()->save();
}
