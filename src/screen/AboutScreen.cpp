#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/AboutScreen.h"
#include "screen/OptionScreen.h"
#include "Game.h"

using namespace sfSnake;

AboutScreen::AboutScreen()
{
    text_.setFont(Game::GlobalFont);
    text_.setString(
        sf::String(L"这是复旦大学2022年春面向对象程序设计课程大作业\n\n") +
        sf::String(L"原作者：jhpy1024(jhpy1024@gmail.com)\n\n") +
        sf::String(L"作者：精益君(JingYiJun3104@outlook.com)\n\n") +
        sf::String(L"The MIT License (MIT) Copyright © 2022 <JingYiJun>"));
    text_.setCharacterSize(Game::GlobalVideoMode.width / 35.0f);
    text_.setFillColor(Game::Color::Green);
    setOriginMiddle(text_);
    text_.setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);

    returnButton_.update("assets/image/returnUI.png", 1 / 16.0f);
    returnButton_.setPosition(Game::GlobalVideoMode.width / 15.0f, Game::GlobalVideoMode.width / 15.0f);
}

void AboutScreen::handleInput(sf::RenderWindow &window)
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
            Game::MainScreen = Game::TmpScreen;
            Game::TmpScreen = nullptr;
            return;
        }
    }
}

void AboutScreen::update(sf::Time delta)
{
    Game::GlobalTitle.update(delta);
}

void AboutScreen::render(sf::RenderWindow &window)
{
    Game::GlobalTitle.render(window);
    returnButton_.render(window);
    window.draw(text_);
}