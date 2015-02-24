#include "SpriteBaseEffect.h"

USING_NS_CC;

SpriteBaseEffect::~SpriteBaseEffect()
{
    if (nullptr != this->_effectSprite)
    {
        this->_effectSprite->release();
        this->_effectSprite = nullptr;
    }
}

bool SpriteBaseEffect::initWithSpriteName(std::string spriteName)
{
    this->_effectSprite = Sprite::create(spriteName);
    this->_effectSprite->retain();
    
    return true;
}
