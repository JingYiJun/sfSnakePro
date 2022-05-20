#include <SFML/Graphics.hpp>

#include <memory>

#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");
    text_.setFont(font_);
    text_.setString(
        "\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
        "\n\nPress [ESC] to quit");

    snakeText_.setFont(font_);
    snakeText_.setString("Snake!");
    snakeText_.setFillColor(sf::Color::Green);
    snakeText_.setCharacterSize(64);
    snakeText_.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 2);

    sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
    snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
                         snakeTextBounds.top + snakeTextBounds.height / 2);
    snakeText_.setPosition(Game::VideoMode_.width / 2, Game::VideoMode_.height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen_ = std::make_shared<GameScreen>();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void MenuScreen::update(sf::Time delta)
{
    static bool movingLeft = false;
    static bool movingRight = true;

    if (movingRight)
    {
        snakeText_.rotate(delta.asSeconds());

        if (static_cast<int>(snakeText_.getRotation()) == 10)
        {
            movingRight = false;
            movingLeft = true;
        }
    }

    if (movingLeft)
    {
        snakeText_.rotate(-delta.asSeconds());

        if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
        {
            movingLeft = false;
            movingRight = true;
        }
    }
}

void MenuScreen::render(sf::RenderWindow &window)
{
    window.draw(text_);
    window.draw(snakeText_);
}