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
    this->showQuestion();
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