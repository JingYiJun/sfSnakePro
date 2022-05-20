#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    optionText_.setFont(font_);
    optionText_.setString(
        "Press [SPACE] to play"
        "\n\nPress [ESC] to quit");
    optionText_.setFillColor(sf::Color(0xd35400ff));
    optionText_.setCharacterSize(Game::VideoMode_.width / 30);

    titleText_.setFont(font_);
    titleText_.setString(L"Snake!");
    titleText_.setFillColor(sf::Color(0x28b463ff));
    titleText_.setCharacterSize(Game::VideoMode_.width / 10);

    sf::FloatRect optionTextBounds = optionText_.getLocalBounds();
    optionText_.setOrigin(optionTextBounds.left + optionTextBounds.width / 2,
                          optionTextBounds.top + optionTextBounds.height / 2);
    optionText_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 3 * 2);

    sf::FloatRect titleTextBounds = titleText_.getLocalBounds();
    titleText_.setOrigin(titleTextBounds.left + titleTextBounds.width / 2,
                         titleTextBounds.top + titleTextBounds.height / 2);
    titleText_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Game::Screen_ = std::make_shared<GameScreen>();
        if (Game::Screen_ == nullptr)
        {
            std::cout << "Fail to create GameScreen"<< std::endl;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void MenuScreen::update(sf::Time delta)
{
    static bool movingLeft = false;
    static bool movingRight = true;

    if (movingRight)
    {
        titleText_.rotate(delta.asSeconds());

        if (static_cast<int>(titleText_.getRotation()) == 10)
        {
            movingRight = false;
            movingLeft = true;
        }
    }

    if (movingLeft)
    {
        titleText_.rotate(-delta.asSeconds());

        if (static_cast<int>(titleText_.getRotation()) == (360 - 10))
        {
            movingLeft = false;
            movingRight = true;
        }
    }
}

void MenuScreen::render(sf::RenderWindow &window)
{
    window.draw(optionText_);
    window.draw(titleText_);
}