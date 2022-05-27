#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/PauseScreen.h"
#include "screen/OptionScreen.h"
#include "screen/HelpScreen.h"
#include "screen/AboutScreen.h"
#include "Game.h"

using namespace sfSnake;

PauseScreen::PauseScreen()
    : button_(3)
{
    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    titleTexture_.loadFromFile("assets/image/logo.png");
    titleTexture_.setSmooth(true);
    titleSprite_.setTexture(titleTexture_);

    sf::FloatRect titleSpriteBounds = setOriginMiddle(titleSprite_);
    titleSprite_.setScale(titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0, titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0);
    titleSprite_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 4);

    button_[0].update("assets/image/optionUI.png");
    button_[1].update("assets/image/restartUI.png");
    button_[2].update("assets/image/exitUI.png");
    returnButton_.update("assets/image/returnUI.png", 1 / 16.0f);

    button_[0].setPosition(Game::VideoMode_.width / 3.0, Game::VideoMode_.height / 5.0 * 3.0);
    button_[1].setPosition(Game::VideoMode_.width / 2.0, Game::VideoMode_.height / 5.0 * 3.0);
    button_[2].setPosition(Game::VideoMode_.width / 3.0 * 2.0, Game::VideoMode_.height / 5.0 * 3.0);
    returnButton_.setPosition(Game::VideoMode_.width / 15.0, Game::VideoMode_.width / 15.0);

    helpButton_.settings(
        L"帮助",
        font_,
        Game::VideoMode_.width / 20.0,
        sf::Color::Green,
        sf::Vector2f(Game::VideoMode_.width / 5.0f * 2.0f, Game::VideoMode_.height / 5.0f * 4.0f));

    aboutButton_.settings(
        L"关于",
        font_,
        Game::VideoMode_.width / 20.0,
        sf::Color::Green,
        sf::Vector2f(Game::VideoMode_.width / 5.0f * 3.0f, Game::VideoMode_.height / 5.0f * 4.0f));
}

void PauseScreen::handleInput(sf::RenderWindow &window)
{
    auto mousePosition = sf::Mouse::getPosition(window);

    for (auto &i : button_)
        i.focused(false);
    returnButton_.focused(false);
    helpButton_.clear();
    aboutButton_.clear();

    if (button_[0].contain(mousePosition))
    {
        button_[0].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen_ = Game::Screen_;
            Game::Screen_ = std::make_shared<OptionScreen>();
            return;
        }
    }

    if (button_[1].contain(mousePosition))
    {
        button_[1].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            Game::Screen_ = std::make_shared<GameScreen>();
            return;
        }
    }

    if (button_[2].contain(mousePosition))
    {
        button_[2].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            window.close();
            return;
        }
    }

    if (returnButton_.contain(mousePosition))
    {
        returnButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            Game::Screen_ = Game::TmpGameScreen_;
            Game::TmpGameScreen_ = nullptr;
            return;
        }
    }

    if (helpButton_.contains(mousePosition))
    {
        helpButton_.focused();
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            helpButton_.seleted();
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen_ = Game::Screen_;
            Game::Screen_ = std::make_shared<HelpScreen>();
            return;
        }
    }

    if (aboutButton_.contains(mousePosition))
    {
        aboutButton_.focused();
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            aboutButton_.seleted();
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen_ = Game::Screen_;
            Game::Screen_ = std::make_shared<AboutScreen>();
            return;
        }
    }
}

void PauseScreen::update(sf::Time delta)
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

void PauseScreen::render(sf::RenderWindow &window)
{
    window.draw(titleSprite_);
    for (auto &button : button_)
    {
        button.render(window);
    }
    returnButton_.render(window);
    helpButton_.render(window);
    aboutButton_.render(window);
}