#include "GamePlayLayer.h"

#include "AppMacros.h"

#include "CharacterNode.h"
#include "Obstruction/SmallCoinNode.h"
#include "Obstruction/IndividualIncomeTaxCoinNode.h"
#include "Obstruction/UrbanMaintenanceAndConstructionTaxCoinNode.h"
#include "Obstruction/BusinessTaxCoinNode.h"
#include "Obstruction/BusinessIncomeTaxCoinNode.h"
#include "Obstruction/BuildingTaxCoinNode.h"
#include "Obstruction/VehicleAndVesselTaxCoinNode.h"
#include "Obstruction/DeedTaxCoinNode.h"
#include "Obstruction/StampTaxCoinNode.h"
#include "Obstruction/FootboardNode.h"
#include "Obstruction/ThornFootboardNode.h"
#include "Obstruction/SoftCloudNode.h"
#include "Obstruction/HeartNode.h"
#include "Obstruction/FlyBootNode.h"
#include "Obstruction/RocketNode.h"
#include "Obstruction/MagnetNode.h"
#include "Obstruction/AngelWingNode.h"
#include "Obstruction/EvilCloudNode.h"
#include "Obstruction/VortexNode.h"
#include "Obstruction/UFONode.h"

USING_NS_CC;

GamePlayLayer::~GamePlayLayer()
{
    if (nullptr != this->_mainGameLayer)
    {
        this->_mainGameLayer->release();
        this->_mainGameLayer = nullptr;
    }
    if (nullptr != this->_characterNode)
    {
        this->_characterNode->release();
        this->_characterNode = nullptr;
    }
}

bool GamePlayLayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(GamePlayLayer::accelerated, this));
    //在事件监听器中注册
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->_visibleSize = Director::getInstance()->getVisibleSize();
    this->_origin = Director::getInstance()->getVisibleOrigin();
    
    auto backgroundSprite = Sprite::create("Background.png");
//    backgroundSprite->setVisible(false);
    backgroundSprite->setScale(1.25f, 1.25f);
    backgroundSprite->setPosition(Vec2(designResolutionSize / 2));
    this->addChild(backgroundSprite);
    
    this->_mainGameLayer = Layer::create();
    this->_mainGameLayer->retain();
    
    auto groundSprite = Sprite::create("Ground.png");
//    groundSprite->setVisible(false);
    groundSprite->setScale(1.25f, 1.25f);
    groundSprite->setPosition(Vec2(designResolutionSize / 2) + Vec2(0.0f, (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
    this->_mainGameLayer->addChild(groundSprite, 0);

    this->_characterNode = CharacterNode::create();
    this->_characterNode->retain();
    this->_characterNode->setObstructionNodeVector(&this->_obstructionVector);
    
    this->_characterNode->setCollisionSize(Size(80.0f, 80.0f));
    this->_characterNode->setCollisionOffset(Vec2(0.0f, -3.0f));
    
    this->_characterNode->setMaxVerticalSpeed(1000.0f);
    this->_characterNode->setMaxHorizontalSpeed(30.0f);
    
    this->_characterNode->setHorizontalMovingRange({0.0f, designResolutionSize.width});
    
    this->_mainGameLayer->addChild(this->_characterNode, 80);
    
    this->addChild(this->_mainGameLayer);
    
    //Test Code//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    cdPlayTime = 0.0f;

    this->_characterNode->setCollisionSize(Size(80.0f * 1.3f, 80.0f * 1.3f));
//    this->_characterNode->setScale(1.3f);

    this->_characterNode->setNormalAcceleration(-1000.0f);
    
    auto node1 = CSLoader::createNode("Layer1.csb");
    node1->setTag(501);
    node1->setPosition(Vec2(-1000.0f, -1000.0f));
//    node1->setVisible(false);
    auto node2 = CSLoader::createNode("Layer2.csb");
    node2->setTag(502);
    node2->setPosition(Vec2(-1000.0f, -1000.0f));
//    node2->setVisible(false);
    auto node3 = CSLoader::createNode("Layer3.csb");
    node3->setTag(503);
    node3->setPosition(Vec2(-1000.0f, -1000.0f));
//    node3->setVisible(false);

    this->_mainGameLayer->addChild(node1, 10);
    this->_mainGameLayer->addChild(node2, 10);
    this->_mainGameLayer->addChild(node3, 10);
    
//    auto subNode = uiNode->getChildByTag(7);
//    subNode->setPosition(Vec2(subNode->getPosition().x, subNode->getPosition().y - (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
//    subNode = uiNode->getChildByTag(8);
//    subNode->setPosition(Vec2(subNode->getPosition().x, subNode->getPosition().y + (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
//    subNode = uiNode->getChildByTag(9);
//    subNode->setPosition(Vec2(subNode->getPosition().x, subNode->getPosition().y + (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
    
    this->_characterNode->setPosition(Vec2(designResolutionSize.width / 2, this->_origin.y + 100.0f));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}

double lastUpdateTime = 0;

double getCurrentTime()
{
    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    gettimeofday(&tv, NULL);
    
    double f = (double)tv.tv_sec + (float)(tv.tv_usec/1000)/(float)1000;
    return f;
}

void GamePlayLayer::gameUpdate(float delta)
{
//    if (1.0f / delta < 50.0f)
//    {
//        log("%f, %f, %f", 1.0f / delta, delta, lastUpdateTime);
//    }
    
    double time1 = getCurrentTime();
    
    for(auto& obstruction : this->_obstructionVector)
    {
        if (InactivatedNodeState != obstruction->getState())
        {
            obstruction->gameUpdate(delta);
        }
    }

    this->_characterNode->gameUpdate(delta);
    
    this->followCharacter();
    this->cleanupUselessObstructions();
    this->buildTopperScene();
    
    
    if (this->_characterNode->getPosition().y - 100.0f > this->getMaxDistance())
    {
        this->setMaxDistance(this->_characterNode->getPosition().y - 100.0f);
    }

    double time2 = getCurrentTime();
    lastUpdateTime = time2 - time1;
    
    if (this->_characterNode->getPosition().y < 0.0f
        || this->_characterNode->getPosition().y < (this->getMaxDistance() - 2 * designResolutionSize.height)
        || this->_characterNode->getHeartCount() <= 0)
    {
        this->setDead(true);
        cdPlayTime = 0.0f;
    }
    else
    {
        cdPlayTime += delta;
        if (cdPlayTime > 4.0f)
        {
            this->startPlay();
            cdPlayTime = -999999999.0f;
        }
    }
}

void GamePlayLayer::accelerated(cocos2d::Acceleration *acceleration, cocos2d::Event *event)
{
    float percentage = acceleration->x;
    this->_characterNode->setHorizontalSpeedPercentage(percentage);
}

void GamePlayLayer::startPlay()
{
    this->_characterNode->startPlay();
}

void GamePlayLayer::revive(int coinCount)
{
    this->setDead(false);
    float newY = this->getMaxDistance() - 2 * designResolutionSize.height;
    newY = newY < 0.0f ? 0.0f : newY;
    this->_characterNode->dropCoins(coinCount);
    this->_characterNode->setPosition(Vec2(this->_characterNode->getPosition().x, newY));
    this->_characterNode->revive();
}

int GamePlayLayer::getHeartCount()
{
    return this->_characterNode->getHeartCount();
}

int GamePlayLayer::getCoinAmount()
{
    return this->_characterNode->getCoinAmount();
}

int GamePlayLayer::getTaxCoinAmount()
{
    return this->_characterNode->getTaxCoinAmount();
}

const TaxCoinMap& GamePlayLayer::getTaxCoinMap()
{
    return this->_characterNode->getTaxCoinMap();
}

BaseEffect* GamePlayLayer::getEffect()
{
    return this->_characterNode->getEffect();
}

void GamePlayLayer::followCharacter()
{
    float newY = designResolutionSize.height / 2.0f - this->_characterNode->getPosition().y;

    if (newY > 0.0f)
    {
        newY = 0.0f;
    }
    
    this->_mainGameLayer->setPosition(Vec2(this->_mainGameLayer->getPosition().x, newY));
}

void GamePlayLayer::cleanupUselessObstructions()
{
    ObstructionVector uselessObstructionVector;
    for(auto& obstruction : this->_obstructionVector)
    {
        if (InactivatedNodeState == obstruction->getState()
            || obstruction->getPosition().y < (this->_characterNode->getPosition().y - designResolutionSize.height * 1.5f))
        {
            obstruction->setVisible(false);
            uselessObstructionVector.pushBack(obstruction);
        }
    }
    for(auto& obstruction : uselessObstructionVector)
    {
        ObstructionPoolMapIterator iter = this->_obstructionPoolMap.find(obstruction->getNodeType());
        if (iter != this->_obstructionPoolMap.end())
        {
            this->_obstructionPoolMap.at(obstruction->getNodeType()).pushBack(obstruction);
        }
        else
        {
            this->_obstructionPoolMap.insert(ObstructionPoolPair(obstruction->getNodeType(), ObstructionVector())).first->second.pushBack(obstruction);
        }

        this->_obstructionVector.eraseObject(obstruction);
    }
}

ObstructionNode* GamePlayLayer::getObstructionNode(ObstructionNodeType nodeType)
{
    ObstructionPoolMapIterator iter = this->_obstructionPoolMap.find(nodeType);
    if (iter != this->_obstructionPoolMap.end())
    {
        if (iter->second.size() > 0)
        {
            auto lastObstruction = iter->second.back();
            this->_obstructionVector.pushBack(lastObstruction);
            iter->second.popBack();

            lastObstruction->reactivate();
            return lastObstruction;
        }
    }
    
    ObstructionNode* obstructionNode = nullptr;
    if (SmallCoinNodeType == nodeType)
    {
        obstructionNode = SmallCoinNode::create();
        obstructionNode->setCollisionSize(Size(60.0f, 60.0f));
    }
    else if (IndividualIncomeTaxCoinNodeType == nodeType)
    {
        obstructionNode = IndividualIncomeTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 88.0f));
    }
    else if (UrbanMaintenanceAndConstructionTaxCoinNodeType == nodeType)
    {
        obstructionNode = UrbanMaintenanceAndConstructionTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 88.0f));
    }
    else if (BusinessTaxCoinNodeType == nodeType)
    {
        obstructionNode = BusinessTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 88.0f));
    }
    else if (BusinessIncomeTaxCoinNodeType == nodeType)
    {
        obstructionNode = BusinessIncomeTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 88.0f));
    }
    else if (BuildingTaxCoinNodeType == nodeType)
    {
        obstructionNode = BuildingTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 89.0f));
    }
    else if (VehicleAndVesselTaxCoinNodeType == nodeType)
    {
        obstructionNode = VehicleAndVesselTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 89.0f));
    }
    else if (DeedTaxCoinNodeType == nodeType)
    {
        obstructionNode = DeedTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 89.0f));
    }
    else if (StampTaxCoinNodeType == nodeType)
    {
        obstructionNode = StampTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 89.0f));
    }
    else if (FootboardNodeType == nodeType)
    {
        obstructionNode = FootboardNode::create();
        obstructionNode->setCollisionSize(Size(150.0f, 92.0f));
    }
    else if (ThornFootboardNodeType == nodeType)
    {
        obstructionNode = ThornFootboardNode::create();
        obstructionNode->setCollisionSize(Size(166.0f, 74.0f));
    }
    else if (SoftCloudNodeType == nodeType)
    {
        obstructionNode = SoftCloudNode::create();
        obstructionNode->setCollisionSize(Size(152.0f, 85.0f));
    }
    else if (HeartNodeType == nodeType)
    {
        obstructionNode = HeartNode::create();
        obstructionNode->setCollisionSize(Size(76.0f, 106.0f));
    }
    else if (FlyBootNodeType == nodeType)
    {
        obstructionNode = FlyBootNode::create();
        obstructionNode->setCollisionSize(Size(72.0f, 53.0f));
    }
    else if (RocketNodeType == nodeType)
    {
        obstructionNode = RocketNode::create();
        obstructionNode->setCollisionSize(Size(59.0f, 103.0f));
    }
    else if (MagnetNodeType == nodeType)
    {
        obstructionNode = MagnetNode::create();
        obstructionNode->setCollisionSize(Size(90.0f, 132.0f));
    }
    else if (AngelWingNodeType == nodeType)
    {
        obstructionNode = AngelWingNode::create();
        obstructionNode->setCollisionSize(Size(91.0f, 62.0f));
    }
    else if (EvilCloudNodeType == nodeType)
    {
        obstructionNode = EvilCloudNode::create();
        obstructionNode->setCollisionSize(Size(152.0f, 85.0f));
    }
    else if (VortexNodeType == nodeType)
    {
        obstructionNode = VortexNode::create();
        obstructionNode->setCollisionSize(Size(152.0f, 144.0f));
    }
    else if (UFONodeType == nodeType)
    {
        obstructionNode = UFONode::create();
        obstructionNode->setCollisionSize(Size(145.0f, 96.0f));
    }

    obstructionNode->setPosition(Vec2());
    obstructionNode->reactivate();
    obstructionNode->setRootNode(this->_mainGameLayer);
    this->_mainGameLayer->addChild(obstructionNode, 50);
    this->_obstructionVector.pushBack(obstructionNode);

    return obstructionNode;
}

void GamePlayLayer::buildTopperScene()
{
    const float buildLineInterval = 180.0f;
    float targetLine = this->_characterNode->getPosition().y + designResolutionSize.height * 1.5f;
    while (targetLine > this->_lastBuildLine + buildLineInterval)
    {
        this->_lastBuildLine += buildLineInterval;
        
        ObstructionNode* gameNode = nullptr;
        static int testI = 0;
        const int m = 20;
        if (testI % m == 0)
        {
            gameNode = this->getObstructionNode(SmallCoinNodeType);
        }
        else if (testI % m == 1)
        {
            gameNode = this->getObstructionNode(IndividualIncomeTaxCoinNodeType);
        }
        else if (testI % m == 2)
        {
            gameNode = this->getObstructionNode(UrbanMaintenanceAndConstructionTaxCoinNodeType);
        }
        else if (testI % m == 3)
        {
            gameNode = this->getObstructionNode(FootboardNodeType);
        }
        else if (testI % m == 4)
        {
            gameNode = this->getObstructionNode((testI % (m * 12)) == 4 ? FlyBootNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 5)
        {
            gameNode = this->getObstructionNode((testI % (m * 18)) == 5 ? RocketNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 6)
        {
            gameNode = this->getObstructionNode((testI % (m * 15)) == 6 ? MagnetNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 7)
        {
            gameNode = this->getObstructionNode(HeartNodeType);
        }
        else if (testI % m == 8)
        {
            gameNode = this->getObstructionNode(BusinessTaxCoinNodeType);
        }
        else if (testI % m == 9)
        {
            gameNode = this->getObstructionNode(BusinessIncomeTaxCoinNodeType);
        }
        else if (testI % m == 10)
        {
            gameNode = this->getObstructionNode((testI % (m * 13)) == 10 ? AngelWingNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 11)
        {
            gameNode = this->getObstructionNode((testI % (m * 14)) == 11 ? EvilCloudNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 12)
        {
            gameNode = this->getObstructionNode((testI % (m * 5)) == 12 ? ThornFootboardNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 13)
        {
            gameNode = this->getObstructionNode((testI % (m * 20)) == 13 ? VortexNodeType : SmallCoinNodeType);
        }
        else if (testI % m == 14)
        {
            gameNode = this->getObstructionNode((testI % (m * 11)) == 14 ? UFONodeType : SmallCoinNodeType);
//            gameNode = this->getObstructionNode(UFONodeType);
        }
        else if (testI % m == 15)
        {
            gameNode = this->getObstructionNode(BuildingTaxCoinNodeType);
        }
        else if (testI % m == 16)
        {
            gameNode = this->getObstructionNode(VehicleAndVesselTaxCoinNodeType);
        }
        else if (testI % m == 17)
        {
            gameNode = this->getObstructionNode(DeedTaxCoinNodeType);
        }
        else if (testI % m == 18)
        {
            gameNode = this->getObstructionNode(StampTaxCoinNodeType);
        }
        else if (testI % m == 19)
        {
            gameNode = this->getObstructionNode(SoftCloudNodeType);
        }
        ++testI;
        
//        auto gameNode = this->getObstructionNode(IndividualIncomeTaxCoin);
        
//        struct  timeval tv;
//        gettimeofday(&tv,NULL);
//        float t = tv.tv_usec / 1000000.0f;
        
        timeval psv;
        gettimeofday( &psv, NULL );
        unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;
        static int seedTest = 0;
        seedTest += 1330;
        seedTest %= 123;
        seedTest += 1560;
        seedTest %= 200;
        srand( tsrans + seedTest );
        float t = rand() % 100 / 100.0f;

        if (gameNode->getNodeType() != UFONodeType)
        {
            gameNode->setPosition(Vec2(t * designResolutionSize.width, this->_lastBuildLine));
        }
        else
        {
            UFONode* ufoNode = static_cast<UFONode*>(gameNode);
            ufoNode->moveWithRange(Vec2(0.0f, this->_lastBuildLine), Vec2(designResolutionSize.width, this->_lastBuildLine));
        }
    }
    
    auto layer1 = this->_mainGameLayer->getChildByTag(501);
    auto layer2 = this->_mainGameLayer->getChildByTag(502);
    auto layer3 = this->_mainGameLayer->getChildByTag(503);
    int factor = (((int)this->_characterNode->getPosition().y) - 640) / 1280;
    
    int phase =  factor % 3;
    switch (phase)
    {
        case 0:
            // 2 1 3
            layer2->setPosition(Vec2(0.0f, 1280.0f * (factor + 1)));
            layer1->setPosition(Vec2(0.0f, 1280.0f * factor));
            layer3->setPosition(Vec2(0.0f, 1280.0f * (factor - 1)));
            break;
        case 1:
            // 3 2 1
            layer3->setPosition(Vec2(0.0f, 1280.0f * (factor + 1)));
            layer2->setPosition(Vec2(0.0f, 1280.0f * factor));
            layer1->setPosition(Vec2(0.0f, 1280.0f * (factor - 1)));
            break;
        case 2:
            // 1 3 2
            layer1->setPosition(Vec2(0.0f, 1280.0f * (factor + 1)));
            layer3->setPosition(Vec2(0.0f, 1280.0f * factor));
            layer2->setPosition(Vec2(0.0f, 1280.0f * (factor - 1)));
            break;
        default:
            break;
    }
    
    layer1->setVisible(factor > 0);
}
