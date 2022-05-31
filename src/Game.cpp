#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <string>

#include "screen/MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

/* Global Color settings
 * 全局颜色设置
 */

const sf::Color Game::Color::Yellow =
    sf::Color(0xf1c40fff);
const sf::Color Game::Color::Green =
    sf::Color(0x2ecc71ff);
const sf::Color Game::Color::Background[] =
    {
        sf::Color(0xeaeaeaee), // White
        sf::Color(0x747474ff), // Black
        sf::Color(0x9f6133aa)  // Brown
};
const sf::Color Game::Color::Grid[] =
    {
        sf::Color(0xfbfbfbaa), // White
        sf::Color(0x31313116), // Black
        sf::Color(0x5a351d16)  // Brown
};
const sf::Color Game::Color::NotSeleted =
    sf::Color(0x00000055);
const sf::Color Game::Color::Fruit[] =
    {
        sf::Color(0x212f3dff), // Black
        sf::Color(0x935116ff), // Brown
        sf::Color(0xe74c3cff), // Red
        sf::Color(0x5dade2ff), // Blue
        sf::Color(0x2ecc71ff)  // Green
};

/* static Golbal VideoMode settings
 * 静态全局视频设置，便于创建合适大小的窗口
 * 并且在界面初始化时定位组件
 */

sf::VideoMode Game::initVideoMode_()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    return sf::VideoMode(
        desktopMode.width / 2.0f,
        desktopMode.height / 2.0f,
        desktopMode.bitsPerPixel);
}

sf::VideoMode Game::GlobalVideoMode = Game::initVideoMode_();

/* Global element
 * 全局的组件就在这里定义好
 * 避免了代码重复，和元素的重复构建
 */

sf::Font Game::GlobalFont = sf::Font();
TitleSprite Game::GlobalTitle = TitleSprite();

/* Global Screen create, originally MenuScreen
 * 生成全局界面对象，开局先进入菜单界面
 * 另外两个界面作为按钮的跳转表
 * 当界面足够复杂和庞大的时候
 * 可能需要用树来存储访问路径
 */

std::shared_ptr<Screen> Game::MainScreen = std::make_shared<MenuScreen>();
std::shared_ptr<Screen> Game::TmpScreen = nullptr;
std::shared_ptr<Screen> Game::TmpGameScreen = nullptr;

/* static global settings
 * 全局设置
 * 包括网格可见性，背景颜色，网格颜色
 */

int Game::GridVisibility = 0;
int Game::GridColor = 0;
int Game::BackgroundColor = 0;

/* static keyboard and mouse lock to prevent misoperation
 * 键盘锁和鼠标锁用于防误触
 */
sf::Clock Game::mouseButtonClock = sf::Clock();
sf::Time Game::mouseButtonCDtime = sf::Time();
bool Game::mouseButtonLocked = false;

sf::Clock Game::keyboardClock = sf::Clock();
sf::Time Game::keyboardCDtime = sf::Time();
bool Game::keyboardLocked = false;

/* 开局显示帮助
 */
bool Game::ifShowedHelp = false;

Game::Game()
    : TimePerFrame_(sf::seconds(1.f / 100.f))
{
    window_.create(
        GlobalVideoMode,   // videoMode
        "sfSnakePro",      // window name
        sf::Style::Close); // window Style
    sf::Image icon;
    icon.loadFromFile("assets/image/favicon.png");
    window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    bgMusic_.openFromFile("assets/music/Roa - Bloom.wav");
    bgMusic_.setVolume(30);
    bgMusic_.setLoop(true);
    bgMusic_.play();
}

void Game::handleInput()
{
    static sf::Event event;

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }

    if (window_.hasFocus() &&
        sf::FloatRect(
            sf::Vector2f(0, 0),
            sf::Vector2f(
                Game::GlobalVideoMode.width,
                Game::GlobalVideoMode.height))
            .contains(static_cast<sf::Vector2f>(
                sf::Mouse::getPosition(window_))))
        Game::MainScreen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
    Game::MainScreen->update(delta);
}

void Game::render()
{
    window_.clear(Color::Background[BackgroundColor]);
    Game::MainScreen->render(window_);
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

        while (timeSinceLastUpdate > TimePerFrame_)
        {
            timeSinceLastUpdate -= TimePerFrame_;
            handleInput();

            update(TimePerFrame_);

            render();
        }

        delta = mouseButtonClock.restart();
        mouseButtonCDtime += delta;

        if (mouseButtonCDtime.asSeconds() > 0.5f)
        {
            mouseButtonCDtime -= sf::seconds(0.5f);
            mouseButtonLocked = false;
        }

        delta = keyboardClock.restart();
        keyboardCDtime += delta;

        if (keyboardCDtime.asSeconds() > 0.5f)
        {
            keyboardCDtime -= sf::seconds(0.5f);
            keyboardLocked = false;
        }
    }
}