#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"
#include "screen/PauseScreen.h"

using namespace sfSnake;

GameScreen::GameScreen()
    : snake_(), grid_(), pauseButton_()
{
    pauseButton_.update("assets/image/pauseUI.png", 1 / 16.0f);
    pauseButton_.setPosition(Game::VideoMode_.width / 15.0 * 14.0, Game::VideoMode_.width / 15.0);

    font_.loadFromFile("assets/fonts/SourceHanSansSC-Bold.otf");

    score_.setFont(font_);
    score_.setString(sf::String(L"分数:") + std::to_string(snake_.getScore()));
    score_.setCharacterSize(Game::VideoMode_.width / 25.0f);
    score_.setFillColor(Game::Color::Yellow);
    setOriginMiddle(score_);
    score_.setPosition(Game::VideoMode_.width / 2.0f, Game::VideoMode_.width * 0.05f);
}

void GameScreen::handleInput(sf::RenderWindow &window)
{
    snake_.handleInput(window);

    static sf::Vector2i mousePosition;
    mousePosition = sf::Mouse::getPosition(window);

    pauseButton_.focused(false);

    if (pauseButton_.contain(mousePosition))
    {
        pauseButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpGameScreen_ = Game::Screen_;
            Game::Screen_ = std::make_shared<PauseScreen>();
            return;
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

    score_.setString(sf::String(L"分数:\t") + std::to_string(snake_.getScore()));
}

void GameScreen::render(sf::RenderWindow &window)
{
    if (Game::GridVisibility_)
        grid_.render(window);
    snake_.render(window);
    for (auto fruit : fruit_)
        fruit.render(window);
    pauseButton_.render(window);
    window.draw(score_);
}

void GameScreen::generateFruit()
{
    static std::default_random_engine engine(time(NULL));
    static std::default_random_engine colorEngine(time(NULL));

    static std::uniform_int_distribution<int> xPos(Game::VideoMode_.width / 15.0f, Game::VideoMode_.width - Game::VideoMode_.width / 10.0f);
    static std::uniform_int_distribution<int> yPos(Game::VideoMode_.width / 10.0f, Game::VideoMode_.height - Game::VideoMode_.width / 15.0f);
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