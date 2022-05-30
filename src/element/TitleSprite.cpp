#include <iostream>

#include "element/TitleSprite.h"
#include "Game.h"

using namespace sfSnake;

TitleSprite::TitleSprite()
    : titleTexture_(), titleSprite_(), rotateDirection_(true)
{
    titleTexture_.loadFromFile("assets/image/logo.png");
    titleTexture_.setSmooth(true);
    titleSprite_.setTexture(titleTexture_);

    sf::FloatRect titleSpriteBounds = setOriginMiddle(titleSprite_);
    titleSprite_.setScale(titleSpriteBounds.width / Game::GlobalVideoMode.width / 5.0 * 4.0, titleSpriteBounds.width / Game::GlobalVideoMode.width / 5.0 * 4.0);
    titleSprite_.setPosition(Game::GlobalVideoMode.width / 2, Game::GlobalVideoMode.height / 4);
}

void TitleSprite::update(sf::Time delta)
{
    if (rotateDirection_)
    {
        titleSprite_.rotate(delta.asSeconds());
        if (titleSprite_.getRotation() >= 10.0f && titleSprite_.getRotation() <= 11.0f)
            rotateDirection_ = false;
    }
    else
    {
        titleSprite_.rotate(-delta.asSeconds());
        if (titleSprite_.getRotation() >= 349.0f && titleSprite_.getRotation() <= 350.0f)
            rotateDirection_ = true;
    }
}

void TitleSprite::render(sf::RenderWindow &window)
{
    window.draw(titleSprite_);
}