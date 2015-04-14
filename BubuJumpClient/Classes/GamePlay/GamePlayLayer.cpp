#include "GamePlayLayer.h"

#include "AppMacros.h"

#include "../CommonUtility.h"

#include "../Data/Local/LoaclManager.h"

#include "../Audio/AudioManager.h"

#include "CharacterNode.h"
#include "Obstruction/Effect/BaseEffect.h"
#include "Obstruction/SmallCoinNode.h"
#include "Obstruction/SmallCoinMoveNode.h"
#include "Obstruction/InvisibleCoinNode.h"
#include "Obstruction/IndividualIncomeTaxCoinNode.h"
#include "Obstruction/UrbanMaintenanceAndConstructionTaxCoinNode.h"
#include "Obstruction/BusinessTaxCoinNode.h"
#include "Obstruction/BusinessIncomeTaxCoinNode.h"
#include "Obstruction/BuildingTaxCoinNode.h"
#include "Obstruction/VehicleAndVesselTaxCoinNode.h"
#include "Obstruction/DeedTaxCoinNode.h"
#include "Obstruction/StampTaxCoinNode.h"
#include "Obstruction/LandValueIncrementTaxCoinNode.h"
#include "Obstruction/UrbanLandUseTaxCoinNode.h"
#include "Obstruction/FootboardNode.h"
#include "Obstruction/FootboardAirNode.h"
#include "Obstruction/FootboardSpaceNode.h"
#include "Obstruction/FootboardCloudNode.h"
#include "Obstruction/FootboardMoveNode.h"
#include "Obstruction/ThornFootboardMoveNode.h"
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
#include "Obstruction/TaxBalloonNode.h"
#include "Obstruction/MeteoriteNode.h"

USING_NS_CC;

const int PHASE_DISTANCE = 83000;
//const int PHASE_DISTANCE = 9000;

GamePlayLayer::~GamePlayLayer()
{
    if (nullptr != this->_mainGameLayer)
    {
        this->_mainGameLayer->release();
        this->_mainGameLayer = nullptr;
    }
    if (nullptr != this->_backgroundSprite)
    {
        this->_backgroundSprite->release();
        this->_backgroundSprite = nullptr;
    }
    if (nullptr != this->_finishLineSprite)
    {
        this->_finishLineSprite->release();
        this->_finishLineSprite = nullptr;
    }
    if (nullptr != this->_clearanceSprite)
    {
        this->_clearanceSprite->release();
        this->_clearanceSprite = nullptr;
    }
    if (nullptr != this->_transitionNode)
    {
        this->_transitionNode->release();
        this->_transitionNode = nullptr;
    }
    if (nullptr != this->_transitionLightsNode)
    {
        this->_transitionLightsNode->release();
        this->_transitionLightsNode = nullptr;
    }
    if (nullptr != this->_lightLayerColor)
    {
        this->_lightLayerColor->release();
        this->_lightLayerColor = nullptr;
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
    
    this->_backgroundSprite = Sprite::create("Background1.png");
    this->_backgroundSprite->retain();
    this->_backgroundSprite->setScale(1.25f, 1.25f);
    this->_backgroundSprite->setPosition(Vec2(designResolutionSize / 2));
    this->addChild(this->_backgroundSprite, 0);
    
    this->_mainGameLayer = Layer::create();
    this->_mainGameLayer->retain();
    
    auto groundSprite = Sprite::create("Ground.png");
//    groundSprite->setVisible(false);
    groundSprite->setScale(1.25f, 1.25f);
    groundSprite->setPosition(Vec2(designResolutionSize / 2) + Vec2(0.0f, (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
    this->_mainGameLayer->addChild(groundSprite, 0);

    this->_finishLineSprite = Sprite::create("FinishLine.png");
    this->_finishLineSprite->retain();
    this->_finishLineSprite->setPosition(Vec2(0.0f, -1000.0f));
    this->_mainGameLayer->addChild(this->_finishLineSprite, 75);
    
    this->_clearanceSprite = Sprite::create("Clearance.png");
    this->_clearanceSprite->retain();
    this->_clearanceSprite->setOpacity(0);
    this->_clearanceSprite->setPosition(Vec2(designResolutionSize.width / 2.0f, this->_visibleSize.height / 4 * 3));
    this->addChild(this->_clearanceSprite, 10);
    
    this->_transitionNode = Node::create();
    this->_transitionNode->retain();
    this->_transitionNode->setVisible(false);
    this->_mainGameLayer->addChild(this->_transitionNode, 25);
    for (int i = 0; i < 100; ++i)
    {
        auto transitionBackgroundSprite = Sprite::create("TransitionBackground.png");
        transitionBackgroundSprite->setPosition(Vec2(0.0f, 1024.0f * i - 128.0f));
        this->_transitionNode->addChild(transitionBackgroundSprite);
    }
    this->_transitionLightsNode = Node::create();
    this->_transitionLightsNode->retain();
    this->_transitionNode->addChild(this->_transitionLightsNode);
    
    this->_lightLayerColor = LayerColor::create(Color4B::WHITE);
    this->_lightLayerColor->retain();
    this->_lightLayerColor->setContentSize(designResolutionSize);
    this->_lightLayerColor->setOpacity(0);
    this->_mainGameLayer->addChild(this->_lightLayerColor, 100);
    
    this->_lastBuildLine = 200.0f;
    
    this->_characterNode = CharacterNode::create();
    this->_characterNode->retain();
    this->_characterNode->setObstructionNodeVector(&this->_obstructionVector);
    
    this->_characterNode->setCollisionSize(Size(80.0f, 80.0f));
    this->_characterNode->setCollisionOffset(Vec2(0.0f, -3.0f));
    
    this->_characterNode->setMaxVerticalSpeed(LoaclManager::getInstance()->getGameConfigData().getMaxVerticalSpeed());
    this->_characterNode->setMaxHorizontalSpeed(LoaclManager::getInstance()->getGameConfigData().getMaxHorizontalSpeed());
    this->_characterNode->setNormalAcceleration(LoaclManager::getInstance()->getGameConfigData().getNormalAcceleration());
    
    this->_characterNode->setHorizontalMovingRange({0.0f, designResolutionSize.width});
    
    this->_mainGameLayer->addChild(this->_characterNode, 80);
    
    this->addChild(this->_mainGameLayer);
    
    //Test Code//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    cdPlayTime = 0.0f;

    this->_characterNode->setCollisionSize(Size(80.0f * 1.3f, 80.0f * 1.3f));
//    this->_characterNode->setScale(1.3f);

    auto node1 = CSLoader::createNode("Phase1.1.csb");
    node1->setTag(501);
    node1->setPosition(Vec2(-1000.0f, -1000.0f));
//    node1->setVisible(false);
    auto node2 = CSLoader::createNode("Phase1.2.csb");
    node2->setTag(502);
    node2->setPosition(Vec2(-1000.0f, -1000.0f));
//    node2->setVisible(false);
    auto node3 = CSLoader::createNode("Phase1.3.csb");
    node3->setTag(503);
    node3->setPosition(Vec2(-1000.0f, -1000.0f));
//    node3->setVisible(false);

    this->_mainGameLayer->addChild(node1, 10);
    this->_mainGameLayer->addChild(node2, 10);
    this->_mainGameLayer->addChild(node3, 10);
    
    groundSprite = Sprite::create("Background2.png");
    node1 = CSLoader::createNode("Phase2.1.csb");
    node2 = CSLoader::createNode("Phase2.2.csb");
    node3 = CSLoader::createNode("Phase2.3.csb");

    groundSprite = Sprite::create("Background3.png");
    node1 = CSLoader::createNode("Phase3.1.csb");
    node2 = CSLoader::createNode("Phase3.2.csb");
    node3 = CSLoader::createNode("Phase3.3.csb");

//    auto subNode = uiNode->getChildByTag(7);
//    subNode->setPosition(Vec2(subNode->getPosition().x, subNode->getPosition().y - (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
//    subNode = uiNode->getChildByTag(8);
//    subNode->setPosition(Vec2(subNode->getPosition().x, subNode->getPosition().y + (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
//    subNode = uiNode->getChildByTag(9);
//    subNode->setPosition(Vec2(subNode->getPosition().x, subNode->getPosition().y + (designResolutionSize.height - this->_visibleSize.height) / 2.0f));
    
    this->_characterNode->setPosition(Vec2(designResolutionSize.width / 2, this->_origin.y + 100.0f));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GamePlayDataVectors& level0GamePlayDataVectors = this->_gamePlayDataLevelMap.insert(IntGamePlayDataVectorPair(0, GamePlayDataVectors())).first->second;

    GamePlayDataVectors& level1GamePlayDataVectors = this->_gamePlayDataLevelMap.insert(IntGamePlayDataVectorPair(1, GamePlayDataVectors())).first->second;

    GamePlayDataVectors& level2GamePlayDataVectors = this->_gamePlayDataLevelMap.insert(IntGamePlayDataVectorPair(2, GamePlayDataVectors())).first->second;

    GamePlayDataVectors& level3GamePlayDataVectors = this->_gamePlayDataLevelMap.insert(IntGamePlayDataVectorPair(3, GamePlayDataVectors())).first->second;

    GamePlayDataVectors& level4GamePlayDataVectors = this->_gamePlayDataLevelMap.insert(IntGamePlayDataVectorPair(4, GamePlayDataVectors())).first->second;

//    std::string path = "/mnt/sdcard/BubuJump/";
//    auto sharedFileUtils = FileUtils::getInstance();
//    if (true == sharedFileUtils->isDirectoryExist(path))
//    {
//        for (int i = 1; i <= 99999; i++)
//        {
//            std::string filePath = path + "Level0." + CommonUtility::convertToString(i) + ".csb";
//            if (true == sharedFileUtils->isFileExist(filePath))
//            {
//                level0GamePlayDataVectors.push_back(GamePlayDataVector());
//                GamePlayDataVector& level0_xGamePlayDataVector = level0GamePlayDataVectors.back();
//                this->readGamePlayDataToVector(filePath, level0_xGamePlayDataVector);
//            }
//            else
//            {
//                break;
//            }
//        }
//
//        for (int i = 1; i <= 99999; i++)
//        {
//            std::string filePath = path + "Level1." + CommonUtility::convertToString(i) + ".csb";
//            if (true == sharedFileUtils->isFileExist(filePath))
//            {
//                level1GamePlayDataVectors.push_back(GamePlayDataVector());
//                GamePlayDataVector& level1_xGamePlayDataVector = level1GamePlayDataVectors.back();
//                this->readGamePlayDataToVector(filePath, level1_xGamePlayDataVector);
//            }
//            else
//            {
//                break;
//            }
//        }
//    }
    
    if (level0GamePlayDataVectors.size() == 0)
    {
        for (int i = 1; i <= 3; i++)
        {
            level0GamePlayDataVectors.push_back(GamePlayDataVector());
            GamePlayDataVector& level1_xGamePlayDataVector = level0GamePlayDataVectors.back();
            this->readGamePlayDataToVector(std::string("Levels/EditorData/Level0.") + CommonUtility::convertToString(i) + ".csb", level1_xGamePlayDataVector);
        }
    }
    if (level1GamePlayDataVectors.size() == 0)
    {
        for (int i = 1; i <= 10; i++)
        {
            level1GamePlayDataVectors.push_back(GamePlayDataVector());
            GamePlayDataVector& level1_xGamePlayDataVector = level1GamePlayDataVectors.back();
            this->readGamePlayDataToVector(std::string("Levels/EditorData/Level1.") + CommonUtility::convertToString(i) + ".csb", level1_xGamePlayDataVector);
        }
    }
    if (level2GamePlayDataVectors.size() == 0)
    {
        for (int i = 1; i <= 10; i++)
        {
            level2GamePlayDataVectors.push_back(GamePlayDataVector());
            GamePlayDataVector& level2_xGamePlayDataVector = level2GamePlayDataVectors.back();
            this->readGamePlayDataToVector(std::string("Levels/EditorData/Level2.") + CommonUtility::convertToString(i) + ".csb", level2_xGamePlayDataVector);
        }
    }
    if (level3GamePlayDataVectors.size() == 0)
    {
        for (int i = 1; i <= 10; i++)
        {
            level3GamePlayDataVectors.push_back(GamePlayDataVector());
            GamePlayDataVector& level3_xGamePlayDataVector = level3GamePlayDataVectors.back();
            this->readGamePlayDataToVector(std::string("Levels/EditorData/Level3.") + CommonUtility::convertToString(i) + ".csb", level3_xGamePlayDataVector);
        }
    }
    if (level4GamePlayDataVectors.size() == 0)
    {
        for (int i = 1; i <= 10; i++)
        {
            level4GamePlayDataVectors.push_back(GamePlayDataVector());
            GamePlayDataVector& level4_xGamePlayDataVector = level4GamePlayDataVectors.back();
            this->readGamePlayDataToVector(std::string("Levels/EditorData/Level4.") + CommonUtility::convertToString(i) + ".csb", level4_xGamePlayDataVector);
        }
    }

    return true;
}

void GamePlayLayer::gameUpdate(float delta)
{
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
    
    int currentTransitionPhase = ((int)(this->_characterNode->getPosition().y - (this->_transitionPhase * 15000.0f))) / PHASE_DISTANCE;
    this->_finishLineSprite->setPosition(designResolutionSize.width / 2.0f, (this->_transitionPhase + 1) * PHASE_DISTANCE + this->_transitionPhase * 15000.0f + 80.0f);
    this->_lightLayerColor->setPosition(Vec2(0.0f, this->_characterNode->getPosition().y - designResolutionSize.height / 2.0f));
    if (currentTransitionPhase > this->_transitionPhase)
    {
        this->_isTransiting = true;
        for(auto& obstruction : this->_obstructionVector)
        {
            obstruction->setState(InactivatedNodeState);
            obstruction->setVisible(false);
        }
        this->_lastBuildLine = this->_characterNode->getPosition().y;
        this->_currentPatternGamePlayDataVector.clear();
        
        this->_transitionPhase = currentTransitionPhase;
        
        this->_transitionNode->setPosition(Vec2(designResolutionSize.width / 2.0f, this->_characterNode->getPosition().y));
        this->_transitionNode->setVisible(true);
        
        timeval psv;
        gettimeofday( &psv, NULL );
        unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;
        static int seedTest = 0;
        srand( tsrans + seedTest );
        for (int i = 15120; i > 0; i -= 200)
        {
            float t = rand() % 100 / 100.0f;
            
            Sprite* lightSprite = Sprite::create("TransitionLight.png");
            lightSprite->setPosition(Vec2(t * designResolutionSize.width - designResolutionSize.width / 2.0f, i));
            this->_transitionLightsNode->addChild(lightSprite);
        }
        this->_transitionLightsNode->setPosition(Vec2(0.0f, -512.0f));
        this->_transitionLightsNode->runAction(MoveBy::create(4.0f, Vec2(0.0f, -2000.0f)));
        
        const static int testDuration = 10;
//        const static int testDuration = FileUtils::getInstance()->getValueVectorFromFile("/mnt/sdcard/BubuJump/Duration.plist").at(0).asInt();
        
        this->_lightLayerColor->setOpacity(255);
        FadeOut* fadeOut1 = FadeOut::create(1.0f);
        DelayTime* delayTime = DelayTime::create(testDuration - 2);
        FadeIn* fadeIn = FadeIn::create(0.0f);
        CallFunc* transitionFinishedCallFunc = CallFunc::create(CC_CALLBACK_0(GamePlayLayer::transitionFinished, this));
        FadeOut* fadeOut2 = FadeOut::create(1.0f);
        Sequence* sequence = Sequence::create(fadeOut1, delayTime, fadeIn, transitionFinishedCallFunc, fadeOut2, nullptr);
        this->_lightLayerColor->runAction(sequence);

        auto effect = EffectFactory::getInstance()->getEffect(TransitionEffectType);
        effect->setCharacterNode(this->_characterNode);
        this->_characterNode->setEffect(effect);
        this->_characterNode->setCurrentSpeed(this->_characterNode->getMaxVerticalSpeed());
        
        AudioManager::getInstance()->playEffect("Sound/sfx-success.wav");
        AudioManager::getInstance()->setLowEffectVolume(true);

        fadeIn = FadeIn::create(1.0f);
        delayTime = DelayTime::create(1.0f);
        fadeOut1 = FadeOut::create(1.0f);
        sequence = Sequence::create(fadeIn, delayTime, fadeOut1, nullptr);
        this->_clearanceSprite->setTexture("Clearance.png");
        this->_clearanceSprite->runAction(sequence);
        
        if (currentTransitionPhase < 2)
        {
            this->_backgroundSprite->setTexture("Background2.png");
            
            auto layer1 = this->_mainGameLayer->getChildByTag(501);
            layer1->removeFromParent();
            auto layer2 = this->_mainGameLayer->getChildByTag(502);
            layer2->removeFromParent();
            auto layer3 = this->_mainGameLayer->getChildByTag(503);
            layer3->removeFromParent();

            auto node1 = CSLoader::createNode("Phase2.1.csb");
            auto actionTimeline1 = CSLoader::createTimeline("Phase2.1.csb");
            node1->runAction(actionTimeline1);
            actionTimeline1->gotoFrameAndPlay(0, true);
            node1->setTag(501);
            node1->setPosition(Vec2(-1000.0f, -1000.0f));
            auto node2 = CSLoader::createNode("Phase2.2.csb");
            auto actionTimeline2 = CSLoader::createTimeline("Phase2.2.csb");
            node2->runAction(actionTimeline2);
            actionTimeline2->gotoFrameAndPlay(0, true);
            node2->setTag(502);
            node2->setPosition(Vec2(-1000.0f, -1000.0f));
            auto node3 = CSLoader::createNode("Phase2.3.csb");
            auto actionTimeline3 = CSLoader::createTimeline("Phase2.3.csb");
            node3->runAction(actionTimeline3);
            actionTimeline3->gotoFrameAndPlay(0, true);
            node3->setTag(503);
            node3->setPosition(Vec2(-1000.0f, -1000.0f));
            
            this->_mainGameLayer->addChild(node1, 10);
            this->_mainGameLayer->addChild(node2, 10);
            this->_mainGameLayer->addChild(node3, 10);

        }
        else if (currentTransitionPhase < 3)
        {
            this->_backgroundSprite->setTexture("Background3.png");
            
            auto layer1 = this->_mainGameLayer->getChildByTag(501);
            layer1->removeFromParent();
            auto layer2 = this->_mainGameLayer->getChildByTag(502);
            layer2->removeFromParent();
            auto layer3 = this->_mainGameLayer->getChildByTag(503);
            layer3->removeFromParent();
            
            auto node1 = CSLoader::createNode("Phase3.1.csb");
            auto actionTimeline1 = CSLoader::createTimeline("Phase3.1.csb");
            node1->runAction(actionTimeline1);
            actionTimeline1->gotoFrameAndPlay(0, true);
            node1->setTag(501);
            node1->setPosition(Vec2(-1000.0f, -1000.0f));
            auto node2 = CSLoader::createNode("Phase3.2.csb");
            auto actionTimeline2 = CSLoader::createTimeline("Phase3.2.csb");
            node2->runAction(actionTimeline2);
            actionTimeline2->gotoFrameAndPlay(0, true);
            node2->setTag(502);
            node2->setPosition(Vec2(-1000.0f, -1000.0f));
            auto node3 = CSLoader::createNode("Phase3.3.csb");
            auto actionTimeline3 = CSLoader::createTimeline("Phase3.3.csb");
            node3->runAction(actionTimeline3);
            actionTimeline3->gotoFrameAndPlay(0, true);
            node3->setTag(503);
            node3->setPosition(Vec2(-1000.0f, -1000.0f));
            
            this->_mainGameLayer->addChild(node1, 10);
            this->_mainGameLayer->addChild(node2, 10);
            this->_mainGameLayer->addChild(node3, 10);
            
            this->_characterNode->setMaxVerticalSpeed(2000.0f);
            this->_characterNode->setNormalAcceleration(-3500.0f);
        }
        else if (currentTransitionPhase < 4)
        {
            this->_backgroundSprite->setTexture("Background4.png");
            
            auto layer1 = this->_mainGameLayer->getChildByTag(501);
            layer1->removeFromParent();
            auto layer2 = this->_mainGameLayer->getChildByTag(502);
            layer2->removeFromParent();
            auto layer3 = this->_mainGameLayer->getChildByTag(503);
            layer3->removeFromParent();
            
            auto node1 = CSLoader::createNode("Phase4.1.csb");
            auto actionTimeline1 = CSLoader::createTimeline("Phase4.1.csb");
            node1->runAction(actionTimeline1);
            actionTimeline1->gotoFrameAndPlay(0, true);
            node1->setTag(501);
            node1->setPosition(Vec2(-1000.0f, -1000.0f));
            auto node2 = CSLoader::createNode("Phase4.2.csb");
            auto actionTimeline2 = CSLoader::createTimeline("Phase4.2.csb");
            node2->runAction(actionTimeline2);
            actionTimeline2->gotoFrameAndPlay(0, true);
            node2->setTag(502);
            node2->setPosition(Vec2(-1000.0f, -1000.0f));
            auto node3 = CSLoader::createNode("Phase4.3.csb");
            auto actionTimeline3 = CSLoader::createTimeline("Phase4.3.csb");
            node3->runAction(actionTimeline3);
            actionTimeline3->gotoFrameAndPlay(0, true);
            node3->setTag(503);
            node3->setPosition(Vec2(-1000.0f, -1000.0f));
            
            this->_mainGameLayer->addChild(node1, 10);
            this->_mainGameLayer->addChild(node2, 10);
            this->_mainGameLayer->addChild(node3, 10);
        }
    }
    
    if (this->_characterNode->getPosition().y - 100.0f > this->getMaxDistance())
    {
        this->setMaxDistance(this->_characterNode->getPosition().y - 100.0f);
    }

    float lowestLine = 1.7E+308;
    for(auto& obstruction : this->_obstructionVector)
    {
        if (ActivatedNodeState == obstruction->getState())
        {
            float newLowestLine = obstruction->getPosition().y - ((obstruction->getCollisionSize().height + this->_characterNode->getCollisionSize().height) / 2.0f) - 100.0f;
            if (newLowestLine < lowestLine)
            {
                lowestLine = newLowestLine;
            }
        }
    }
    
    if (this->_characterNode->getPosition().y < lowestLine && this->_characterNode->getPosition().y > (designResolutionSize.height / 2.0f) && Downing == this->_characterNode->getActionState() && this->_characterNode->getCurrentSpeed() < -(this->_characterNode->getMaxVerticalSpeed()))
    {
        if (0 == this->_characterNode->getNumberOfRunningActions()
            && (nullptr == this->_characterNode->getEffect() || InactivatedEffectState == this->_characterNode->getEffect()->getState() || RocketEffectType != this->_characterNode->getEffect()->getType()))
        {
            this->_characterNode->setMode(Dead);
            
            auto sequenceAction = Sequence::create(RotateTo::create(0.25f, 180), RotateTo::create(0.25f, 360), NULL);
            this->_characterNode->runAction(Repeat::create(sequenceAction, 999));
            
            AudioManager::getInstance()->playEffect("Sound/sfx-player-die.aac");
        }
    }
    
    if (this->_characterNode->getMode() == Dead)
    {
        if (0 == this->_characterNode->getNumberOfRunningActions())
        {
            auto sequenceAction = Sequence::create(RotateTo::create(0.25f, 180), RotateTo::create(0.25f, 360), NULL);
            this->_characterNode->runAction(Repeat::create(sequenceAction, 999));
            
            AudioManager::getInstance()->playEffect("Sound/sfx-player-die.aac");
        }
    }
    
    if (this->_characterNode->getPosition().y < 0.0f
        || this->_characterNode->getPosition().y < (this->getMaxDistance() - 3 * designResolutionSize.height))
    {
        this->setDead(true);
//        cdPlayTime = 0.0f;
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
//    auto fadeIn = FadeIn::create(1.0f);
//    auto delayTime = DelayTime::create(1.0f);
//    auto fadeOut1 = FadeOut::create(1.0f);
//    auto sequence = Sequence::create(fadeIn, delayTime, fadeOut1, nullptr);
//    int indexNo = this->_transitionPhase <= 3 ? this->_transitionPhase : 3;
//    this->_clearanceSprite->setTexture("Welcome" + CommonUtility::convertToString(indexNo + 1) + ".png");
//    this->_clearanceSprite->runAction(sequence);

    auto tapJumpTipsSprite = Sprite::create("TapJumpTips.png");
    this->getParent()->addChild(tapJumpTipsSprite);
    tapJumpTipsSprite->setPosition((designResolutionSize / 2.0f) - Size(0.0f, 200.0f));
    auto delayTime = DelayTime::create(5.0f);
    auto fadeOut = FadeOut::create(1.0f);
    auto sequence = Sequence::create(delayTime, fadeOut, NULL);
    tapJumpTipsSprite->runAction(sequence);
    
    this->_characterNode->startPlay();
}

void GamePlayLayer::revive(int coinCount)
{
    if (coinCount < 10)
    {
        ++(this->_qaReviveCount);
    }
    
    this->setDead(false);
    float newY = this->getMaxDistance() - 2 * designResolutionSize.height;
    newY = newY < 0.0f ? 0.0f : newY;
    this->_characterNode->dropCoins(coinCount);
    this->_characterNode->setPosition(Vec2(this->_characterNode->getPosition().x, newY));
    this->_characterNode->stopAllActions();
    this->_characterNode->setRotation(0.0f);
    this->_characterNode->revive();
    
    AudioManager::getInstance()->playEffect("Sound/sfx-rocket.aac");
}

void GamePlayLayer::goJump()
{
    this->_characterNode->goJump();
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
    else if (SmallCoinMoveNodeType == nodeType)
    {
        obstructionNode = SmallCoinMoveNode::create();
        obstructionNode->setCollisionSize(Size(60.0f, 60.0f));
    }
    else if (InvisibleCoinNodeType == nodeType)
    {
        obstructionNode = InvisibleCoinNode::create();
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
    else if (LandValueIncrementTaxCoinNodeType == nodeType)
    {
        obstructionNode = LandValueIncrementTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 89.0f));
    }
    else if (UrbanLandUseTaxCoinNodeType == nodeType)
    {
        obstructionNode = UrbanLandUseTaxCoinNode::create();
        obstructionNode->setCollisionSize(Size(89.0f, 89.0f));
    }
    else if (FootboardNodeType == nodeType)
    {
        obstructionNode = FootboardNode::create();
        obstructionNode->setCollisionSize(Size(150.0f, 92.0f));
    }
    else if (FootboardAirNodeType == nodeType)
    {
        obstructionNode = FootboardAirNode::create();
        obstructionNode->setCollisionSize(Size(186.0f, 83.0f));
    }
    else if (FootboardSpaceNodeType == nodeType)
    {
        obstructionNode = FootboardSpaceNode::create();
        obstructionNode->setCollisionSize(Size(185.0f, 86.0f));
    }
    else if (FootboardCloudNodeType == nodeType)
    {
        obstructionNode = FootboardCloudNode::create();
        obstructionNode->setCollisionSize(Size(150.0f, 92.0f));
    }
    else if (FootboardMoveNodeType == nodeType)
    {
        obstructionNode = FootboardMoveNode::create();
        obstructionNode->setCollisionSize(Size(138.0f, 93.0f));
    }
    else if (ThornFootboardNodeType == nodeType)
    {
        obstructionNode = ThornFootboardNode::create();
        obstructionNode->setCollisionSize(Size(150.0f, 60.0f));
    }
    else if (ThornFootboardMoveNodeType == nodeType)
    {
        obstructionNode = ThornFootboardMoveNode::create();
        obstructionNode->setCollisionSize(Size(150.0f, 60.0f));
    }
    else if (SoftCloudNodeType == nodeType)
    {
        obstructionNode = SoftCloudNode::create();
        obstructionNode->setCollisionSize(Size(152.0f, 71.0f));
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
    else if (TaxBalloonNodeType == nodeType)
    {
        obstructionNode = TaxBalloonNode::create();
        obstructionNode->setCollisionSize(Size(107.0f, 133.0f));
    }
    else if (MeteoriteNodeType == nodeType)
    {
        obstructionNode = MeteoriteNode::create();
        obstructionNode->setCollisionSize(Size(99.0f, 99.0f));
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
    const float buildLineInterval = 120.0f;
    float targetLine = this->_characterNode->getPosition().y + designResolutionSize.height * 1.5f;
    while (targetLine > this->_lastBuildLine + buildLineInterval)
    {
        this->_lastBuildLine += buildLineInterval;

        if (0 == this->_currentPatternGamePlayDataVector.size())
        {
            int levelPatternIndex = 0;
            if (false == this->_isTransiting)
            {
                levelPatternIndex = this->_transitionPhase + 1;
                if (levelPatternIndex >= this->_gamePlayDataLevelMap.size())
                {
                    levelPatternIndex = (int)this->_gamePlayDataLevelMap.size() - 1;
                }
            }
            GamePlayDataVectors& gamePlayDataVectors = (*this->_gamePlayDataLevelMap.find(levelPatternIndex)).second;
            
            static int seed = 0;
            if (0 == seed)
            {
                timeval psv;
                gettimeofday( &psv, NULL );
                unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;
                seed = tsrans;
            }
            srand(seed);
            double start = 0;
            double end = gamePlayDataVectors.size();
            int random = rand();
            int r = start + (end - start) * random / (RAND_MAX + 1.0);
            seed = random;
            
            this->_currentPatternGamePlayDataVector = gamePlayDataVectors.at(r);
            
            this->_patternLowestLine = 99999999.0f;
            for (GamePlayData& gamePlayData : this->_currentPatternGamePlayDataVector)
            {
                if (gamePlayData.position.y < this->_patternLowestLine)
                {
                    this->_patternLowestLine = gamePlayData.position.y;
                }
            }
            
            this->_patternStartLine = this->_lastBuildLine;
        }
        else
        {
            float patternBuildLine = this->_patternLowestLine + (this->_lastBuildLine - this->_patternStartLine);
            for (GamePlayDataVectorIter iter = this->_currentPatternGamePlayDataVector.begin(); iter != this->_currentPatternGamePlayDataVector.end();)
            {
                GamePlayData& gamePlayData = *iter;
                if (gamePlayData.position.y <= patternBuildLine)
                {
                    ObstructionNode* gameNode = nullptr;

                    if (CommonUtility::isStringStartWith(gamePlayData.typeName, "SmallCoinMove"))
                    {
                        gameNode = this->getObstructionNode(SmallCoinMoveNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "SmallCoin"))
                    {
                        gameNode = this->getObstructionNode(SmallCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "InvisibleCoin"))
                    {
                        gameNode = this->getObstructionNode(InvisibleCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "IndividualIncomeTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(IndividualIncomeTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "UrbanMaintenanceAndConstructionTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(UrbanMaintenanceAndConstructionTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "BusinessTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(BusinessTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "BusinessIncomeTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(BusinessIncomeTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "BuildingTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(BuildingTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "VehicleAndVesselTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(VehicleAndVesselTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "DeedTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(DeedTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "StampTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(StampTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "LandValueIncrementTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(LandValueIncrementTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "UrbanLandUseTaxCoin"))
                    {
                        gameNode = this->getObstructionNode(UrbanLandUseTaxCoinNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "FootboardAir"))
                    {
                        gameNode = this->getObstructionNode(FootboardAirNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "FootboardSpace"))
                    {
                        gameNode = this->getObstructionNode(FootboardSpaceNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "FootboardCloud"))
                    {
                        gameNode = this->getObstructionNode(FootboardCloudNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "FootboardMove"))
                    {
                        gameNode = this->getObstructionNode(FootboardMoveNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "Footboard"))
                    {
                        gameNode = this->getObstructionNode(FootboardNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "ThornFootboardMove"))
                    {
                        gameNode = this->getObstructionNode(ThornFootboardMoveNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "ThornFootboard"))
                    {
                        gameNode = this->getObstructionNode(ThornFootboardNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "SoftCloud"))
                    {
                        gameNode = this->getObstructionNode(SoftCloudNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "Heart"))
                    {
                        gameNode = this->getObstructionNode(HeartNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "FlyBoot"))
                    {
                        gameNode = this->getObstructionNode(FlyBootNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "Rocket"))
                    {
                        gameNode = this->getObstructionNode(RocketNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "Magnet"))
                    {
                        gameNode = this->getObstructionNode(MagnetNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "AngelWing"))
                    {
                        gameNode = this->getObstructionNode(AngelWingNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "EvilCloud"))
                    {
                        gameNode = this->getObstructionNode(EvilCloudNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "Vortex"))
                    {
                        gameNode = this->getObstructionNode(VortexNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "UFO"))
                    {
                        gameNode = this->getObstructionNode(UFONodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "TaxBalloon"))
                    {
                        gameNode = this->getObstructionNode(TaxBalloonNodeType);
                    }
                    else if (CommonUtility::isStringStartWith(gamePlayData.typeName, "Meteorite"))
                    {
                        gameNode = this->getObstructionNode(MeteoriteNodeType);
                    }
                    
                    Vec2 newPosition = Vec2(gamePlayData.position.x, gamePlayData.position.y - this->_patternLowestLine + this->_patternStartLine);
                    
                    if (UFONodeType == gameNode->getNodeType())
                    {
                        UFONode* ufoNode = static_cast<UFONode*>(gameNode);
                        ufoNode->moveWithRange(Vec2(0.0f, newPosition.y), Vec2(designResolutionSize.width, newPosition.y));
                    }
                    else if (SmallCoinMoveNodeType == gameNode->getNodeType())
                    {
                        SmallCoinMoveNode* smallCoinMoveNode = static_cast<SmallCoinMoveNode*>(gameNode);
                        if (gamePlayData.moveDistance > 0.1f || gamePlayData.moveDistance < -0.1f)
                        {
                            smallCoinMoveNode->moveWithRange(newPosition, newPosition + Vec2(gamePlayData.moveDistance, 0.0f));
                        }
                        else
                        {
                            smallCoinMoveNode->stopAllActions();
                            smallCoinMoveNode->setPosition(newPosition);
                        }
                    }
                    else if (FootboardMoveNodeType == gameNode->getNodeType())
                    {
                        FootboardMoveNode* footboardMoveNode = static_cast<FootboardMoveNode*>(gameNode);
                        if (gamePlayData.moveDistance > 0.1f || gamePlayData.moveDistance < -0.1f)
                        {
                            footboardMoveNode->moveWithRange(newPosition, newPosition + Vec2(gamePlayData.moveDistance, 0.0f));
                        }
                        else
                        {
                            footboardMoveNode->stopAllActions();
                            footboardMoveNode->setPosition(newPosition);
                        }
                    }
                    else if (ThornFootboardMoveNodeType == gameNode->getNodeType())
                    {
                        ThornFootboardMoveNode* thornFootboardMoveNode = static_cast<ThornFootboardMoveNode*>(gameNode);
                        if (gamePlayData.moveDistance > 0.1f || gamePlayData.moveDistance < -0.1f)
                        {
                            thornFootboardMoveNode->moveWithRange(newPosition, newPosition + Vec2(gamePlayData.moveDistance, 0.0f));
                        }
                        else
                        {
                            thornFootboardMoveNode->stopAllActions();
                            thornFootboardMoveNode->setPosition(newPosition);
                        }
                    }
                    else if (TaxBalloonNodeType == gameNode->getNodeType())
                    {
                        TaxBalloonNode* taxBalloonNode = static_cast<TaxBalloonNode*>(gameNode);
                        if (gamePlayData.moveDistance > 0.1f || gamePlayData.moveDistance < -0.1f)
                        {
                            taxBalloonNode->moveWithRange(newPosition, newPosition + Vec2(gamePlayData.moveDistance, 0.0f));
                        }
                        else
                        {
                            taxBalloonNode->stopAllActions();
                            taxBalloonNode->setPosition(newPosition);
                        }
                    }
                    else if (MeteoriteNodeType == gameNode->getNodeType())
                    {
                        MeteoriteNode* meteoriteNode = static_cast<MeteoriteNode*>(gameNode);
                        if (gamePlayData.moveDistance > 0.1f || gamePlayData.moveDistance < -0.1f)
                        {
                            meteoriteNode->moveWithRange(newPosition, newPosition + Vec2(gamePlayData.moveDistance, 0.0f));
                        }
                        else
                        {
                            meteoriteNode->stopAllActions();
                            meteoriteNode->setPosition(newPosition);
                        }
                    }
                    else
                    {
                        if (InvisibleCoinNodeType == gameNode->getNodeType())
                        {
                            InvisibleCoinNode* invisibleCoinNode = static_cast<InvisibleCoinNode*>(gameNode);
                            invisibleCoinNode->setCharacterNode(this->_characterNode);
                        }
                        gameNode->setPosition(newPosition);
                    }
                    
                    iter = this->_currentPatternGamePlayDataVector.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
        }
    }
    
    const static int shiftHeight = 2560;
    
    auto layer1 = this->_mainGameLayer->getChildByTag(501);
    auto layer2 = this->_mainGameLayer->getChildByTag(502);
    auto layer3 = this->_mainGameLayer->getChildByTag(503);
    int factor = (((int)this->_characterNode->getPosition().y) - 640) / shiftHeight;
    
    int phase =  factor % 3;
    switch (phase)
    {
        case 0:
            // 2 1 3
            layer2->setPosition(Vec2(0.0f, shiftHeight * (factor + 1)));
            layer1->setPosition(Vec2(0.0f, shiftHeight * factor));
            layer3->setPosition(Vec2(0.0f, shiftHeight * (factor - 1)));
            break;
        case 1:
            // 3 2 1
            layer3->setPosition(Vec2(0.0f, shiftHeight * (factor + 1)));
            layer2->setPosition(Vec2(0.0f, shiftHeight * factor));
            layer1->setPosition(Vec2(0.0f, shiftHeight * (factor - 1)));
            break;
        case 2:
            // 1 3 2
            layer1->setPosition(Vec2(0.0f, shiftHeight * (factor + 1)));
            layer3->setPosition(Vec2(0.0f, shiftHeight * factor));
            layer2->setPosition(Vec2(0.0f, shiftHeight * (factor - 1)));
            break;
        default:
            break;
    }
    
    layer1->setVisible(factor > 0);
}

void GamePlayLayer::transitionFinished()
{
    AudioManager::getInstance()->setLowEffectVolume(false);

    this->_isTransiting = false;

    for(auto& obstruction : this->_obstructionVector)
    {
        obstruction->setState(InactivatedNodeState);
        obstruction->setVisible(false);
    }
    this->_lastBuildLine = this->_characterNode->getPosition().y;
    this->_currentPatternGamePlayDataVector.clear();

    auto fadeIn = FadeIn::create(1.0f);
    auto delayTime = DelayTime::create(1.0f);
    auto fadeOut1 = FadeOut::create(1.0f);
    auto sequence = Sequence::create(fadeIn, delayTime, fadeOut1, nullptr);
    int indexNo = this->_transitionPhase <= 3 ? this->_transitionPhase : 3;
    this->_clearanceSprite->setTexture("Welcome" + CommonUtility::convertToString(indexNo + 1) + ".png");
    this->_clearanceSprite->runAction(sequence);

    this->_transitionNode->setVisible(false);
    this->_transitionLightsNode->stopAllActions();
    this->_transitionLightsNode->removeAllChildren();
}

void GamePlayLayer::readGamePlayDataToVector(std::string csbName, GamePlayDataVector &gamePlayDataVector)
{
    auto uiNode = CSLoader::createNode(csbName);
    for (Node* node : uiNode->getChildren())
    {
        GamePlayData gamePlayData;
        gamePlayData.typeName = node->getName();
        gamePlayData.position = node->getPosition();
        gamePlayData.moveDistance = node->getRotationSkewX();
        gamePlayDataVector.push_back(gamePlayData);
    }
}
