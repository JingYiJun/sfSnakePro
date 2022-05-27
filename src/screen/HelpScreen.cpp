#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/HelpScreen.h"
#include "screen/OptionScreen.h"
#include "Game.h"

using namespace sfSnake;

HelpScreen::HelpScreen()
{
    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    titleTexture_.loadFromFile("assets/image/logo.png");
    titleTexture_.setSmooth(true);
    titleSprite_.setTexture(titleTexture_);

    sf::FloatRect titleSpriteBounds = setOriginMiddle(titleSprite_);
    titleSprite_.setScale(titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0, titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0);
    titleSprite_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 4);

    text_.setFont(font_);
    text_.setString(
        sf::String(L"游戏中，按[w/a/s/d]或者[上下左右]键切换方向\n\n") +
        sf::String(L"长按空格加速\n\n") +
        sf::String(L"或者点击鼠标，指引蛇的移动"));
    text_.setCharacterSize(Game::VideoMode_.width / 35.0f);
    text_.setFillColor(Game::Color::Green);
    setOriginMiddle(text_);
    text_.setPosition(Game::VideoMode_.width / 2.0, Game::VideoMode_.height / 5.0 * 3.0);

    returnButton_.update("assets/image/returnUI.png", 1 / 16.0f);
    returnButton_.setPosition(Game::VideoMode_.width / 15.0f, Game::VideoMode_.width / 15.0f);
}

void HelpScreen::handleInput(sf::RenderWindow &window)
{
    auto mousePosition = sf::Mouse::getPosition(window);

    returnButton_.focused(false);
    if (returnButton_.contain(mousePosition))
    {
        returnButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::Screen_ = Game::TmpScreen_;
            Game::TmpScreen_ = nullptr;
            return;
        }
    }
}

void HelpScreen::update(sf::Time delta)
{
    static bool movingLeft = false;
    static bool movingRight = true;

    if (movingRight)
    {
        titleSprite_.rotate(delta.asSeconds());

        if (static_cast<int>(titleSprite_.getRotation()) == 10)
        {
            movingRight = false;
            movingLeft = true;
        }
    }

    if (movingLeft)
    {
        titleSprite_.rotate(-delta.asSeconds());

        if (static_cast<int>(titleSprite_.getRotation()) == (360 - 10))
        {
            movingLeft = false;
            movingRight = true;
        }
    }
}

void HelpScreen::render(sf::RenderWindow &window)
{
    window.draw(titleSprite_);
    returnButton_.render(window);
    window.draw(text_);
}