#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"
#include "screen/OptionScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
    snake_.handleInput(window);

    if (!Game::keyboardLocked)
    {
        static bool keyboardPressed;
        keyboardPressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            Game::GridVisibility_ = 1 ^ Game::GridVisibility_;
            keyboardPressed = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Game::TmpScreen_ = Game::Screen_;
            Game::Screen_ = std::make_shared<OptionScreen>();
            keyboardPressed = true;
        }

        if (keyboardPressed)
        {
            Game::keyboardClock.restart();
            Game::keyboardLocked = true;
        }
    }
}

void GameScreen::update(sf::Time delta)
{
    while (fruit_.size() < 5)
        generateFruit();

    snake_.update(delta);
    snake_.checkFruitCollisions(fruit_);

    if (snake_.hitSelf())
    {
        Game::Screen_ = std::make_shared<GameOverScreen>(snake_.getScore());
    }
}

void GameScreen::render(sf::RenderWindow &window)
{
    if (Game::GridVisibility_)
        grid_.render(window);
    snake_.render(window);
    for (auto fruit : fruit_)
        fruit.render(window);
}

void GameScreen::generateFruit()
{
    static std::default_random_engine engine(time(NULL));
    static std::default_random_engine colorEngine(time(NULL));

    static std::uniform_int_distribution<int> xPos(Fruit::Radius * 4, Game::VideoMode_.width - Fruit::Radius * 4);
    static std::uniform_int_distribution<int> yPos(Fruit::Radius * 4, Game::VideoMode_.height - Fruit::Radius * 4);
    static std::uniform_int_distribution<int> fruitColor(0, 7);

    switch (fruitColor(colorEngine))
    {
    case 0: // black
        fruit_.push_back(Fruit(
            sf::Vector2f(xPos(engine), yPos(engine)),
            sf::Color(0x212f3dff),
            0));
        break;
    case 1: // brown
        fruit_.push_back(Fruit(
            sf::Vector2f(xPos(engine), yPos(engine)),
            sf::Color(0x935116ff),
            0));
        break;
    case 2:
    case 3:
        fruit_.push_back(Fruit(
            sf::Vector2f(xPos(engine), yPos(engine)),
            sf::Color(0xe74c3cff),
            3));
        break;
    case 4:
    case 5:
        fruit_.push_back(Fruit(
            sf::Vector2f(xPos(engine), yPos(engine)),
            sf::Color(0x5dade2ff),
            2));
        break;
    case 6:
    case 7:
        fruit_.push_back(Fruit(
            sf::Vector2f(xPos(engine), yPos(engine)),
            sf::Color(0x2ecc71ff),
            1));
        break;
    default:
        break;
    }
}