#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>

#include "element/Snake.h"
#include "Game.h"
#include "element/Fruit.h"

#include "screen/GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

static double dis(SnakePathNode node1, SnakePathNode node2)
{
    return std::sqrt(std::pow((node1.x - node2.x), 2) + std::pow((node1.y - node2.y), 2));
}

Snake::Snake()
    : hitSelf_(false),
      direction_(Direction(0, -1)),
      nodeRadius_(Game::VideoMode_.width / 100.0f),
      tailOverlap_(0u),
      nodeShape(nodeRadius_),
      nodeMiddle(sf::Vector2f(nodeRadius_ * std::sqrt(3), nodeRadius_)),
      score_(InitialSize)
{
    initNodes();

    nodeShape.setFillColor(sf::Color(0xf1c40fff));

    nodeMiddle.setFillColor(sf::Color(0x1c2833ff));

    sf::FloatRect nodeShapeBounds = nodeShape.getLocalBounds();
    nodeShape.setOrigin(
        nodeShapeBounds.left + nodeShapeBounds.width / 2,
        nodeShapeBounds.top + nodeShapeBounds.height / 2);

    sf::FloatRect nodeMiddleBounds = nodeMiddle.getLocalBounds();
    nodeMiddle.setOrigin(
        nodeMiddleBounds.left + nodeMiddleBounds.width / 2,
        nodeMiddleBounds.top + nodeMiddleBounds.height / 2);

    headTexture.loadFromFile("assets/image/snakeHeadImage.png");
    headTexture.setSmooth(true);
    sf::Vector2u TextureSize = headTexture.getSize();
    float headScale = nodeRadius_ / TextureSize.y * 2.6;
    headSprite.setTexture(headTexture);
    headSprite.setScale(headScale, headScale);

    sf::FloatRect headBounds = headSprite.getLocalBounds();
    headSprite.setOrigin(
        headBounds.left + headBounds.width / 2,
        headBounds.top + headBounds.height / 2);

    pickupBuffer_.loadFromFile("assets/sounds/pickup.wav");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    dieBuffer_.loadFromFile("assets/sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

void Snake::initNodes()
{
    path_.push_back(SnakePathNode(
        Game::VideoMode_.width / 2.0f,
        Game::VideoMode_.height / 2.0f));
    for (int i = 1; i <= 10 * InitialSize; i++)
    {
        path_.push_back(SnakePathNode(
            Game::VideoMode_.width / 2.0f - direction_.x * i * nodeRadius_ / 5.0,
            Game::VideoMode_.height / 2.0f - direction_.y * i * nodeRadius_ / 5.0));
    }
}

void Snake::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction_ = Direction(0, -1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction_ = Direction(0, 1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction_ = Direction(-1, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction_ = Direction(1, 0);

    static double directionSize;

    // Supported MouseControl
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        direction_ = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - toWindow(path_.front());
        directionSize = dis(direction_, sf::Vector2f(0, 0));
        direction_.x /= directionSize;
        direction_.y /= directionSize;
    }

    // Supported Joystick
    if (sf::Joystick::isConnected(0))
    {
        float posX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float posY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        if (std::fabs(posX) >= 1e5 && std::fabs(posX) >= 1e5)
        {
            direction_ = sf::Vector2f(posX, -posY);
            directionSize = dis(direction_, sf::Vector2f(0, 0));
            direction_.x /= directionSize;
            direction_.y /= directionSize;
        }
    }
}

void Snake::update(sf::Time delta)
{
    move();
    static int count = 0;
    if (++count >= 40)
    {
        checkOutOfWindow();
        count -= 40;
    }
    checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::deque<Fruit> &fruits)
{
    auto toRemove = fruits.end();
    SnakePathNode headnode = path_.front();

    for (auto i = fruits.begin(); i != fruits.end(); ++i)
    {
        if (dis(i->shape_.getPosition(), toWindow(headnode)) < nodeRadius_ + i->Radius)
            toRemove = i;
    }

    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        grow(toRemove->score_);
        fruits.erase(toRemove);
    }
}

void Snake::grow(int score)
{
    tailOverlap_ += score * 10;
    score_ += score;
}

unsigned Snake::getScore() const
{
    return score_;
}

bool Snake::hitSelf() const
{
    return hitSelf_;
}

void Snake::move()
{
    SnakePathNode &headNode = path_.front();
    path_.push_front(SnakePathNode(
        headNode.x + direction_.x * nodeRadius_ / 5.0,
        headNode.y + direction_.y * nodeRadius_ / 5.0));
    if (tailOverlap_)
        --tailOverlap_;
    else
        path_.pop_back();
}

void Snake::checkSelfCollisions()
{
    SnakePathNode head = toWindow(path_.front());
    int count = 0;

    for (auto i = path_.begin(); i != path_.end(); i++, count++)
        if (count >= 30 && dis(head, toWindow(*i)) < 2.0f * nodeRadius_)
        {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
            break;
        }
}

void Snake::checkOutOfWindow()
{
    auto inWindow = [](SnakePathNode &node) -> bool
    { return node.x >= 0 && node.x <= Game::VideoMode_.width && node.y >= 0 && node.y <= Game::VideoMode_.height; };
    bool OutOfWindow = true;
    for (auto i : path_)
    {
        if (inWindow(i))
            OutOfWindow = false;
    }
    if (OutOfWindow)
    {
        SnakePathNode &tail = path_.back();
        if (tail.x < 0)
            for (auto &i : path_)
                i.x = i.x + Game::VideoMode_.width;
        else if (tail.x > Game::VideoMode_.width)
            for (auto &i : path_)
                i.x = i.x - Game::VideoMode_.width;
        else if (tail.y < 0)
            for (auto &i : path_)
                i.y = i.y + Game::VideoMode_.height;
        else if (tail.y > Game::VideoMode_.height)
            for (auto &i : path_)
                i.y = i.y - Game::VideoMode_.height;
    }
}

SnakePathNode Snake::toWindow(SnakePathNode node)
{
    while (node.x < 0)
        node.x = node.x + Game::VideoMode_.width;
    while (node.x > Game::VideoMode_.width)
        node.x = node.x - Game::VideoMode_.width;
    while (node.y < 0)
        node.y = node.y + Game::VideoMode_.height;
    while (node.y > Game::VideoMode_.height)
        node.y = node.y - Game::VideoMode_.height;
    return node;
}

void Snake::render(sf::RenderWindow &window)
{
    static int count;
    static SnakePathNode lastSnakeNode, lastMiddleNode, nowSnakeNode;
    static float angle;
    static sf::Vector2f recDirection;
    static SnakePathNode wNowHeadNode;

    lastSnakeNode = *path_.begin();
    wNowHeadNode = toWindow(lastSnakeNode);
    headSprite.setPosition(wNowHeadNode);
    recDirection = direction_;
    angle = std::acos(recDirection.y / dis(recDirection, sf::Vector2f(0.f, 0.f))) / 3.14159265358979323846 * 180.0;
    if (direction_.x > 0)
        angle = -angle;
    headSprite.setRotation(angle);

    renderNode(wNowHeadNode, headSprite, window, 3);

    count = 1;
    for (auto i = path_.begin() + 1; i != path_.end(); i++, count++)
    {
        if (count % 5 == 0)
        {
            if (count % 2)
                lastMiddleNode = *i;
            else
            {
                nowSnakeNode = *i;

                recDirection = nowSnakeNode - lastSnakeNode;
                angle = std::acos(recDirection.y / dis(recDirection, sf::Vector2f(0.f, 0.f))) / 3.14159265358979323846 * 180.0;
                if (recDirection.x > 0)
                    angle = -angle;
                nodeMiddle.setRotation(angle);

                static SnakePathNode wNowSnakeNode;
                static SnakePathNode wMiddleNode;
                wNowSnakeNode = toWindow(nowSnakeNode);
                wMiddleNode = toWindow(lastMiddleNode);
                renderNode(wNowSnakeNode, nodeShape, window, 0);
                renderNode(wMiddleNode, nodeMiddle, window, 0);

                lastSnakeNode = nowSnakeNode;
            }
        }
    }
}

template <typename T>
void Snake::renderNode(sf::Vector2f &nowPosition, T &shape, sf::RenderWindow &window, int offset)
{
    shape.setPosition(nowPosition);
    window.draw(shape);

    if (nowPosition.x <= nodeRadius_ + offset)
    {
        shape.setPosition(nowPosition + sf::Vector2f(Game::VideoMode_.width, 0));
        window.draw(shape);
    }
    else if (nowPosition.x >= Game::VideoMode_.width - nodeRadius_ - offset)
    {
        shape.setPosition(nowPosition - sf::Vector2f(Game::VideoMode_.width, 0));
        window.draw(shape);
    }

    if (nowPosition.y <= nodeRadius_ + offset)
    {
        shape.setPosition(nowPosition + sf::Vector2f(0, Game::VideoMode_.height));
        window.draw(shape);
    }
    else if (nowPosition.y >= Game::VideoMode_.height - nodeRadius_ - offset)
    {
        shape.setPosition(nowPosition - sf::Vector2f(0, Game::VideoMode_.height));
        window.draw(shape);
    }

    if (nowPosition.x <= nodeRadius_ + offset && nowPosition.y <= nodeRadius_ + offset)
    {
        shape.setPosition(nowPosition + sf::Vector2f(Game::VideoMode_.width, Game::VideoMode_.height));
        window.draw(shape);
    }
    else if (nowPosition.x >= Game::VideoMode_.width - nodeRadius_ - offset && nowPosition.y >= Game::VideoMode_.height - nodeRadius_ - offset)
    {
        shape.setPosition(nowPosition - sf::Vector2f(Game::VideoMode_.width, Game::VideoMode_.height));
        window.draw(shape);
    }
}