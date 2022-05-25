#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "screen/OptionScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
    : button_(3)
{
    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    titleTexture_.loadFromFile("assets/image/logo.png");
    titleTexture_.setSmooth(true);
    titleSprite_.setTexture(titleTexture_);

    sf::FloatRect titleSpriteBounds = setOriginMiddle(titleSprite_);
    titleSprite_.setScale(titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0, titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0);
    titleSprite_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 4);

    button_[0].update("assets/image/optionUI.png", 1 / 8.0f);
    button_[1].update("assets/image/startUI.png", 1 / 8.0f);
    button_[2].update("assets/image/exitUI.png", 1 / 8.0f);

    button_[0].sprite_.setPosition(Game::VideoMode_.width / 3.0, Game::VideoMode_.height / 5.0 * 3.0);
    button_[1].sprite_.setPosition(Game::VideoMode_.width / 2.0, Game::VideoMode_.height / 5.0 * 3.0);
    button_[2].sprite_.setPosition(Game::VideoMode_.width / 3.0 * 2.0, Game::VideoMode_.height / 5.0 * 3.0);
}

void MenuScreen::handleInput(sf::RenderWindow &window)
{
    switch (Game::inputDevice)
    {
    case 0:
        break;

    case 1:
        static sf::Vector2i mousePosition;
        mousePosition = sf::Mouse::getPosition(window);

        for (auto &i : button_)
        {
            i.focused_ = false;
        }

        if (dis(mousePosition, button_[0].sprite_.getPosition()) < (button_[0].sprite_.getGlobalBounds().width / 2.0))
        {
            button_[0].focused_ = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::TmpScreen_ = Game::Screen_;
                Game::Screen_ = std::make_shared<OptionScreen>();
                Game::mouseButtonCDtime = sf::Time::Zero;
                Game::mouseButtonLocked = true;
                return;
            }
        }

        if (dis(mousePosition, button_[1].sprite_.getPosition()) < (button_[1].sprite_.getGlobalBounds().width / 2.0))
        {
            button_[1].focused_ = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen_ = std::make_shared<GameScreen>();
                Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
                Game::mouseButtonLocked = true;
                return;
            }
        }

        if (dis(mousePosition, button_[2].sprite_.getPosition()) < (button_[2].sprite_.getGlobalBounds().width / 2.0))
        {
            button_[2].focused_ = true;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                window.close();
                return;
            }
        }

    default:
        break;
    }
}

void MenuScreen::update(sf::Time delta)
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

void MenuScreen::render(sf::RenderWindow &window)
{
    window.draw(titleSprite_);
    for (auto &[tex, sprite, focused] : button_)
    {
        if (focused)
        {
            sprite.setColor(sf::Color(sf::Color::Green));
            window.draw(sprite);
            sprite.setColor(sf::Color(sf::Color::White));
        }
        else
            window.draw(sprite);
    }
}