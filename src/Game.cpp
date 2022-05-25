#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <string>

#include "screen/MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

// VideoMode settings, static!
sf::VideoMode Game::initVideoMode_()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    return sf::VideoMode(
        desktopMode.width / 2.0f,
        desktopMode.height / 2.0f,
        desktopMode.bitsPerPixel);
}

sf::VideoMode Game::VideoMode_ = Game::initVideoMode_();

// Global Screen create, originally MenuScreen
std::shared_ptr<Screen> Game::Screen_ = std::make_shared<MenuScreen>();
std::shared_ptr<Screen> Game::TmpScreen_ = nullptr;

int Game::GridVisibility_ = 0;
int Game::BackgroundColor_ = 0;
int Game::GridColor_ = 0;
sf::Clock Game::mouseButtonClock = sf::Clock();
sf::Clock Game::keyboardClock = sf::Clock();
sf::Time Game::mouseButtonCDtime = sf::Time();
sf::Time Game::keyboardCDtime = sf::Time();

bool Game::mouseButtonLocked = false;
bool Game::keyboardLocked = false;
int Game::inputDevice = 0;

const sf::Color Game::Color::Yellow = sf::Color(0xf1c40fff);
const sf::Color Game::Color::Green = sf::Color(0x98d37aff);
const sf::Color Game::Color::Background[] = {sf::Color(0xeaeaeaee), sf::Color(0x747474ff), sf::Color(0x9f6133ff)};
const sf::Color Game::Color::Grid[] = {sf::Color(0xfbfbfbaa), sf::Color(0x31313116), sf::Color(0x5a351d16)};
const sf::Color Game::Color::NotSeleted = sf::Color(0x00000055);

Game::Game()
    : TimePerFrame(sf::seconds(1.f / 100.f))
{
    // window create
    window_.create(
        VideoMode_,                              // videoMode
        "sfSnake",                               // window name
        sf::Style::Close | sf::Style::Titlebar); // window Style

    // initialize bgMusic
    bgMusic_.openFromFile("assets/music/bg_music.wav");
    bgMusic_.setLoop(true);
    bgMusic_.play();
}

void Game::handleInput()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            inputDevice = 0;
            window_.setMouseCursorVisible(false);
            break;
        case sf::Event::MouseMoved:
            inputDevice = 1;
            window_.setMouseCursorVisible(true);
            break;
        case sf::Event::JoystickMoved:
        case sf::Event::JoystickButtonPressed:
            inputDevice = 2;
            window_.setMouseCursorVisible(false);
            break;
        case sf::Event::Closed:
            window_.close();
            break;
        default:
            break;
        }
    }

    Game::Screen_->handleInput(window_);
}

void Game::update(sf::Time delta)
{
    Game::Screen_->update(delta);
}

void Game::render()
{
    window_.clear(Color::Background[BackgroundColor_]);
    Game::Screen_->render(window_);
    window_.display();
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mouseButtonClock.restart();
    keyboardClock.restart();

    while (window_.isOpen())
    {
        sf::Time delta = clock.restart();
        timeSinceLastUpdate += delta;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            handleInput();

            // update according to time Delta
            update(TimePerFrame);

            // limit the FramePerSecond;
            render();
        }

        delta = mouseButtonClock.restart();
        mouseButtonCDtime += delta;

        while (mouseButtonCDtime.asSeconds() > 0.5f)
        {
            mouseButtonCDtime -= sf::seconds(0.5f);
            mouseButtonLocked = false;
        }

        delta = keyboardClock.restart();
        keyboardCDtime += delta;

        while (keyboardCDtime.asSeconds() > 0.5f)
        {
            keyboardCDtime -= sf::seconds(0.5f);
            keyboardLocked = false;
        }
    }
}

Button::Button()
    : focused_{false}
{
}

void Button::update(std::string filename, float scale)
{
    if (!texture_.loadFromFile(filename))
        std::cout << "error" << std::endl;
    texture_.setSmooth(true);
    sprite_.setTexture(texture_);
    sf::FloatRect bounds = setOriginMiddle(sprite_);
    sprite_.setScale(Game::VideoMode_.width / bounds.width * scale, Game::VideoMode_.width / bounds.width * scale);
}