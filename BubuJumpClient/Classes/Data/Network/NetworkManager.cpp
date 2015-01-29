#include "NetworkManager.h"

#include "json/rapidjson.h"
#include "json/document.h"

#include "../../CommonUtility.h"
#include "../md5.h"

USING_NS_CC;
using namespace cocos2d::network;

//const std::string SERVER_ADDRESS = "http://localhost/";
const std::string SERVER_ADDRESS = "http://bubujump.sinaapp.com/";
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

int NetworkManager::submitScore(int score, NetworkCallback callback)
{
    std::string scoreString = CommonUtility::convertToString(score);
    
    std::string idString = CommonUtility::convertToString(this->_testID);
    
    std::string url = SERVER_ADDRESS + "leaderboard.php";
    url += "?type=1";
    url += "&id=";
    url += idString;
    url += "&name=TestName";
    url += "&score=";
    url += scoreString;
    url += "&sum=";
    
    url += md5SumString("1", idString, "TestName", scoreString);
    
    int index = this->getRequestIndex();
    NetworkCallbackObject& callbackObject = this->_callbackMap.insert(NetworkCallbackPair(index, {callback, false})).first->second;
    
    HttpRequest* request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(NetworkManager::scoreSubmitted, this));
    request->setTag("submitScore");
    request->setUserData(&callbackObject);
    HttpClient::getInstance()->send(request);
    request->release();
    
    return index;
}

int NetworkManager::getRequestIndex()
{
    return ++_nextIndex;
}

void NetworkManager::scoreSubmitted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    NetworkCallbackObject* callbackObject = static_cast<NetworkCallbackObject*>(response->getHttpRequest()->getUserData());
    if (true == callbackObject->canceled)
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

    LeaderboardRecordVector recordVector;
    
    int sameScorePlace = document["sameScorePlace"].GetInt();
    int myID = document["myID"].GetInt();
    int myScore = document["myScore"].GetInt();
    
    this->_testID = myID;
    
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
    
    myRecord->setName("Me");

    LeaderboardRecordVector resultRecordVector;
    if (leaderboardArray.Size() <= 6)
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
        for (int i = 1; resultRecordVector.size() < 6; ++i)
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