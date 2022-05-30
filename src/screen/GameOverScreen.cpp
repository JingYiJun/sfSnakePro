#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"
#include "screen/HelpScreen.h"
#include "screen/AboutScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score)
    : button_(3), score_(score)
{
    text_.setFont(Game::GlobalFont);
    text_.setString(sf::String(L"最终分数：") + std::to_string(score));
    text_.setFillColor(Game::Color::Yellow);
    text_.setCharacterSize(Game::GlobalVideoMode.width / 15);
    setOriginMiddle(text_);
    text_.setPosition(Game::GlobalVideoMode.width / 2.0f, Game::GlobalVideoMode.height / 4.0f);

    button_[0].update("assets/image/optionUI.png");
    button_[1].update("assets/image/restartUI.png");
    button_[2].update("assets/image/exitUI.png");

    button_[0].setPosition(Game::GlobalVideoMode.width / 3.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[1].setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[2].setPosition(Game::GlobalVideoMode.width / 3.0 * 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);

    helpButton_.settings(
        L"帮助",
        Game::GlobalFont,
        Game::GlobalVideoMode.width / 20.0,
        Game::Color::Green,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 2.0f, Game::GlobalVideoMode.height / 5.0f * 4.0f));

    aboutButton_.settings(
        L"关于",
        Game::GlobalFont,
        Game::GlobalVideoMode.width / 20.0,
        Game::Color::Green,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 3.0f, Game::GlobalVideoMode.height / 5.0f * 4.0f));
}

void GameOverScreen::handleInput(sf::RenderWindow &window)
{
    static sf::Vector2i mousePosition;
    mousePosition = sf::Mouse::getPosition(window);

    for (auto &i : button_)
        i.focused(false);
    helpButton_.clear();
    aboutButton_.clear();

    if (button_[0].contain(mousePosition))
    {
        button_[0].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen = Game::MainScreen;
            Game::MainScreen = std::make_shared<OptionScreen>();
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
            Game::MainScreen = std::make_shared<GameScreen>();
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

    if (helpButton_.contains(mousePosition))
    {
        helpButton_.focused();
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            helpButton_.seleted();
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen = Game::MainScreen;
            Game::MainScreen = std::make_shared<HelpScreen>();
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
            Game::TmpScreen = Game::MainScreen;
            Game::MainScreen = std::make_shared<AboutScreen>();
            return;
        }
    }
}

void GameOverScreen::update(sf::Time delta)
{
}

void GameOverScreen::render(sf::RenderWindow &window)
{
    window.draw(text_);
    for (auto &button : button_)
        button.render(window);
    helpButton_.render(window);
    aboutButton_.render(window);
}