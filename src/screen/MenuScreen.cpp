#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
    : buttonTexture_{{"option", sf::Texture()}, {"start", sf::Texture()}, {"exit", sf::Texture()}},
      buttonSprite_{{"option", sf::Sprite()}, {"start", sf::Sprite()}, {"exit", sf::Sprite()}},
      buttonFocused_{{"option", false}, {"start", false}, {"exit", false}}
{
    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    titleTexture_.loadFromFile("assets/image/logo.png");
    titleTexture_.setSmooth(true);
    titleSprite_.setTexture(titleTexture_);

    sf::FloatRect titleSpriteBounds = setOriginMiddle(titleSprite_);
    titleSprite_.setScale(titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0, titleSpriteBounds.width / Game::VideoMode_.width / 5.0 * 4.0);
    titleSprite_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 4);

    buttonTexture_["option"].loadFromFile("assets/image/optionUI.png");
    buttonTexture_["start"].loadFromFile("assets/image/startUI.png");
    buttonTexture_["exit"].loadFromFile("assets/image/exitUI.png");

    buttonSprite_["option"].setTexture(buttonTexture_["option"]);
    buttonSprite_["start"].setTexture(buttonTexture_["start"]);
    buttonSprite_["exit"].setTexture(buttonTexture_["exit"]);

    for (auto &[key, value] : buttonTexture_)
        value.setSmooth(true);

    for (auto &[key, value] : buttonSprite_)
    {
        sf::FloatRect Bounds = setOriginMiddle(value);
        value.setScale(Game::VideoMode_.width / Bounds.width / 8.0, Game::VideoMode_.width / Bounds.width / 8.0);
    }

    buttonSprite_["option"].setPosition(Game::VideoMode_.width / 3.0, Game::VideoMode_.height / 5.0 * 3.0);
    buttonSprite_["start"].setPosition(Game::VideoMode_.width / 2.0, Game::VideoMode_.height / 5.0 * 3.0);
    buttonSprite_["exit"].setPosition(Game::VideoMode_.width / 3.0 * 2.0, Game::VideoMode_.height / 5.0 * 3.0);
}

void MenuScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Game::Screen_ = std::make_shared<GameScreen>();
        return;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    static sf::Vector2i mousePosition;
    mousePosition = sf::Mouse::getPosition(window);

    for (auto &[key, value] : buttonFocused_)
    {
        value = false;
    }

    if (dis(mousePosition, buttonSprite_["option"].getPosition()) < (buttonSprite_["option"].getGlobalBounds().width / 2.0))
    {
        buttonFocused_["option"] = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::Screen_ = std::make_shared<GameScreen>();
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            return;
        }
    }

    if (dis(mousePosition, buttonSprite_["start"].getPosition()) < (buttonSprite_["start"].getGlobalBounds().width / 2.0))
    {
        buttonFocused_["start"] = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::Screen_ = std::make_shared<GameScreen>();
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            return;
        }
    }

    if (dis(mousePosition, buttonSprite_["exit"].getPosition()) < (buttonSprite_["exit"].getGlobalBounds().width / 2.0))
    {
        buttonFocused_["exit"] = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            window.close();
            return;
        }
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
    for (auto &[key, value] : buttonSprite_)
    {
        if (buttonFocused_[key] == true)
        {
            value.setColor(sf::Color(sf::Color::Blue));
            window.draw(value);
            value.setColor(sf::Color(sf::Color::White));
        }
        else
        {
            window.draw(value);
        }
    }
}