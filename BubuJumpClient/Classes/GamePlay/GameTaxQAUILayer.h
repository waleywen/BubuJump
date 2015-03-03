#ifndef _GameTaxQAUILayer_H_
#define _GameTaxQAUILayer_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GamePlayLayer;

typedef typename std::vector<std::string> StringVector;

struct QAData
{
    int type;
    std::string question;
    StringVector options;
    int answer;
};

typedef typename std::vector<QAData> QADataVector;

class GameTaxQAUILayer : public cocos2d::Layer
{
public:
    GameTaxQAUILayer() : _taxCoinSprite(nullptr), _titleLabel(nullptr), _questionLabel(nullptr), _answerLabel1(nullptr), _answerLabel2(nullptr), _answerLabel3(nullptr), _answerLabel4(nullptr), _resultLabel(nullptr), _resultNodeEventListener(nullptr), _qaDataVector(), _qa1Index(-1), _qa2Index(-1), _qa3Index(-1), _score(0), _currentAnswer(-1) {};
    virtual ~GameTaxQAUILayer();
    
    virtual bool init() override;

    CREATE_FUNC(GameTaxQAUILayer);
    
    CC_SYNTHESIZE(GamePlayLayer*, _gamePlayLayer, GamePlayLayer);
private:
    void homeButtonClicked(cocos2d::Ref* sender);
    void cellButtonClicked(cocos2d::Ref* sender);
    void confirmButtonClicked(cocos2d::Ref* sender);
    
    void showQuestion();
    
    void showResultPanel();
    
    cocos2d::Sprite* _taxCoinSprite;
    cocos2d::ui::Text* _titleLabel;
    cocos2d::ui::Text* _questionLabel;
    cocos2d::ui::Text* _answerLabel1;
    cocos2d::ui::Text* _answerLabel2;
    cocos2d::ui::Text* _answerLabel3;
    cocos2d::ui::Text* _answerLabel4;
    
    cocos2d::ui::Text* _resultLabel;
    
    cocos2d::EventListenerTouchOneByOne* _resultNodeEventListener;
    
    QADataVector _qaDataVector;
    int _qa1Index;
    int _qa2Index;
    int _qa3Index;
    
    int _score;
    int _currentAnswer;
};

#endif // _GameTaxQAUILayer_H_
