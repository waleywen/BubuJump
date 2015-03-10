#include "GameTaxQAUILayer.h"

#include "cocostudio/CocoStudio.h"

#include "../AppMacros.h"
#include "../UIHelper.h"
#include "../CommonUtility.h"

#include "GamePlayLayer.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

GameTaxQAUILayer::~GameTaxQAUILayer()
{
    if (nullptr != this->_taxCoinSprite)
    {
        this->_taxCoinSprite->release();
        this->_taxCoinSprite = nullptr;
    }
    if (nullptr != this->_titleLabel)
    {
        this->_titleLabel->release();
        this->_titleLabel = nullptr;
    }
    if (nullptr != this->_questionLabel)
    {
        this->_questionLabel->release();
        this->_questionLabel = nullptr;
    }
    if (nullptr != this->_answerLabel1)
    {
        this->_answerLabel1->release();
        this->_answerLabel1 = nullptr;
    }
    if (nullptr != this->_answerLabel2)
    {
        this->_answerLabel2->release();
        this->_answerLabel2 = nullptr;
    }
    if (nullptr != this->_answerLabel3)
    {
        this->_answerLabel3->release();
        this->_answerLabel3 = nullptr;
    }
    if (nullptr != this->_answerLabel4)
    {
        this->_answerLabel4->release();
        this->_answerLabel4 = nullptr;
    }
    if (nullptr != this->_resultLabel)
    {
        this->_resultLabel->release();
        this->_resultLabel = nullptr;
    }
}

bool GameTaxQAUILayer::init()
{
    if (false == Layer::init())
    {
        return false;
    }
    
    auto uiNode = CSLoader::createNode("GameTaxQAUI.csb");
    this->addChild(uiNode);
    
    auto homeButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "homeButton"));
    homeButton->addClickEventListener(CC_CALLBACK_1(GameTaxQAUILayer::homeButtonClicked, this));
    auto cellButton1 = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "cellButton1"));
    cellButton1->addClickEventListener(CC_CALLBACK_1(GameTaxQAUILayer::cellButtonClicked, this));
    auto cellButton2 = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "cellButton2"));
    cellButton2->addClickEventListener(CC_CALLBACK_1(GameTaxQAUILayer::cellButtonClicked, this));
    auto cellButton3 = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "cellButton3"));
    cellButton3->addClickEventListener(CC_CALLBACK_1(GameTaxQAUILayer::cellButtonClicked, this));
    auto cellButton4 = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "cellButton4"));
    cellButton4->addClickEventListener(CC_CALLBACK_1(GameTaxQAUILayer::cellButtonClicked, this));

    this->_taxCoinSprite = static_cast<Sprite*>(UIHelper::seekNodeByName(uiNode, "taxCoinSprite"));
    this->_taxCoinSprite->retain();
    this->_titleLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "titleLabel"));
    this->_titleLabel->retain();
    this->_questionLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "questionLabel"));
    this->_questionLabel->retain();
    this->_answerLabel1 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "answerLabel1"));
    this->_answerLabel1->retain();
    this->_answerLabel2 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "answerLabel2"));
    this->_answerLabel2->retain();
    this->_answerLabel3 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "answerLabel3"));
    this->_answerLabel3->retain();
    this->_answerLabel4 = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "answerLabel4"));
    this->_answerLabel4->retain();
    
    this->_resultLabel = static_cast<Text*>(UIHelper::seekNodeByName(uiNode, "resultLabel"));
    this->_resultLabel->retain();

    auto resultNode = this->_resultLabel->getParent();
    LayerColor* layerColor = LayerColor::create(Color4B(166, 166, 166, 128), designResolutionSize.width, designResolutionSize.height);
    this->_resultNodeEventListener = EventListenerTouchOneByOne::create();
    this->_resultNodeEventListener->setSwallowTouches(true);
    this->_resultNodeEventListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(this->_resultNodeEventListener, layerColor);
    resultNode->addChild(layerColor, -1);
    resultNode->setPosition(Vec2(-1000.0f, -1000.0f));
    this->_resultNodeEventListener->setEnabled(false);
    
    auto confirmButton = static_cast<Button*>(UIHelper::seekNodeByName(uiNode, "confirmButton"));
    confirmButton->addClickEventListener(CC_CALLBACK_1(GameTaxQAUILayer::confirmButtonClicked, this));

    ValueVector qaVector = FileUtils::getInstance()->getValueVectorFromFile("TaxQA.plist");
    for (Value oneQA : qaVector)
    {
        const ValueMap& qaMap = oneQA.asValueMap();
        QAData qaData;
        qaData.type = qaMap.at("type").asInt();
        qaData.question = qaMap.at("question").asString();
        qaData.answer = qaMap.at("answer").asInt();
        for (Value optionValue : qaMap.at("options").asValueVector())
        {
            qaData.options.push_back(optionValue.asString());
        }
        this->_qaDataVector.push_back(qaData);
    }
    
    this->showQuestion();
    
    return true;
}

void GameTaxQAUILayer::homeButtonClicked(cocos2d::Ref *sender)
{
    Director::getInstance()->popToRootScene();
}

void GameTaxQAUILayer::cellButtonClicked(cocos2d::Ref *sender)
{
    if (1 == this->_currentAnswer && static_cast<Button*>(sender)->getName() == "cellButton1")
    {
        ++(this->_score);
    }
    else if (2 == this->_currentAnswer && static_cast<Button*>(sender)->getName() == "cellButton2")
    {
        ++(this->_score);
    }
    else if (3 == this->_currentAnswer && static_cast<Button*>(sender)->getName() == "cellButton3")
    {
        ++(this->_score);
    }
    else if (4 == this->_currentAnswer && static_cast<Button*>(sender)->getName() == "cellButton4")
    {
        ++(this->_score);
    }
    if (-1 != this->_qa3Index)
    {
        this->_resultLabel->getParent()->setPosition(Vec2::ZERO);
        this->_resultNodeEventListener->setEnabled(true);
        
        auto faceSprite1 = static_cast<Sprite*>(UIHelper::seekNodeByName(this, "faceSprite1"));
        auto faceSprite2 = static_cast<Sprite*>(UIHelper::seekNodeByName(this, "faceSprite2"));
        auto faceSprite3 = static_cast<Sprite*>(UIHelper::seekNodeByName(this, "faceSprite3"));
        
        switch (this->_score)
        {
            case 0:
                this->_resultLabel->setString("很遗憾，全部回答\n错误，复活失败。");
                faceSprite3->setVisible(true);
                break;
            case 1:
                this->_resultLabel->setString("很遗憾，你只答对\n1题，复活失败。");
                faceSprite3->setVisible(true);
                break;
            case 2:
                this->_resultLabel->setString("及格，你答对2\n题，再接再厉。");
                faceSprite2->setVisible(true);
                break;
            case 3:
                this->_resultLabel->setString("真棒！你是税务知\n识小达人！");
                faceSprite1->setVisible(true);
                break;
                
            default:
                break;
        }
        return;
    }
    this->showQuestion();
}

void GameTaxQAUILayer::confirmButtonClicked(cocos2d::Ref *sender)
{
    if (this->_score > 1)
    {
        this->getGamePlayLayer()->revive(0);
        Director::getInstance()->popScene();
    }
    else
    {
        Director::getInstance()->popToRootScene();
    }
}

void GameTaxQAUILayer::showQuestion()
{
    int currentQuestionIndex = 0;
    
    timeval psv;
    gettimeofday( &psv, NULL );
    unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000;
    static int seedTest = 0;
    seedTest += 1330;
    seedTest %= 123;
    seedTest += 1560;
    seedTest %= 200;
    srand( tsrans + seedTest );
    rand();
    rand();
    rand();
    double start = 0;
    double end = this->_qaDataVector.size();
    while (true)
    {
        int r = start + (end - start) * rand() / (RAND_MAX + 1.0);
        if (this->_qa1Index == -1)
        {
            this->_qa1Index = r;
        }
        else if (this->_qa2Index == -1)
        {
            if (this->_qa1Index == r)
            {
                continue;
            }
            this->_qa2Index = r;
        }
        else
        {
            if (this->_qa1Index == r || this->_qa2Index == r)
            {
                continue;
            }
            this->_qa3Index = r;
        }
        currentQuestionIndex = r;
        break;
    }
    
    const QAData& qaData = this->_qaDataVector.at(currentQuestionIndex);
    switch (qaData.type)
    {
        case 1:
            this->_taxCoinSprite->setTexture("IndividualIncomeTaxCoin.png");
            this->_titleLabel->setString("个人所得税");
            break;
        case 2:
            this->_taxCoinSprite->setTexture("BusinessIncomeTaxCoin.png");
            this->_titleLabel->setString("企业所得税");
            break;
        case 3:
            this->_taxCoinSprite->setTexture("BusinessTaxCoin.png");
            this->_titleLabel->setString("营业税");
            break;
        case 4:
            this->_taxCoinSprite->setTexture("UrbanMaintenanceAndConstructionTaxCoin.png");
            this->_titleLabel->setString("城市维护建设税");
            break;
        case 5:
            this->_taxCoinSprite->setTexture("StampTaxCoin.png");
            this->_titleLabel->setString("印花税");
            break;
        case 6:
            this->_taxCoinSprite->setTexture("VehicleAndVesselTaxCoin.png");
            this->_titleLabel->setString("车船税");
            break;
        case 7:
            this->_taxCoinSprite->setTexture("BuildingTaxCoin.png");
            this->_titleLabel->setString("房产税");
            break;
        case 8:
            this->_taxCoinSprite->setTexture("DeedTaxCoin.png");
            this->_titleLabel->setString("契税");
            break;
        case 9:
            this->_taxCoinSprite->setTexture("UrbanLandUseTaxCoin.png");
            this->_titleLabel->setString("城镇土地使用税");
            break;
        case 10:
            this->_taxCoinSprite->setTexture("LandValueIncrementTaxCoin.png");
            this->_titleLabel->setString("土地增值税");
            break;
        case 11:
            this->_taxCoinSprite->setTexture("SmallCoin.png");
            this->_titleLabel->setString("其它");
            break;
        default:
            break;
    }
    
    this->_questionLabel->setString(qaData.question);
    
    this->_answerLabel1->getParent()->setVisible(false);
    this->_answerLabel2->getParent()->setVisible(false);
    this->_answerLabel3->getParent()->setVisible(false);
    this->_answerLabel4->getParent()->setVisible(false);
    for (int i = 0; i < qaData.options.size(); ++i)
    {
        Text* answerLabel = nullptr;
        switch (i)
        {
            case 0:
                answerLabel = this->_answerLabel1;
                break;
            case 1:
                answerLabel = this->_answerLabel2;
                break;
            case 2:
                answerLabel = this->_answerLabel3;
                break;
            case 3:
                answerLabel = this->_answerLabel4;
                break;
                
            default:
                break;
        }
        answerLabel->setString(qaData.options.at(i));
        answerLabel->getParent()->setVisible(true);
    }
    
    this->_currentAnswer = qaData.answer;
}

void GameTaxQAUILayer::showResultPanel()
{
    
}
