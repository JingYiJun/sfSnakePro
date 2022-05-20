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
      nodeShape(nodeRadius_),
      nodeMiddle(sf::Vector2f(nodeRadius_ * std::sqrt(3), nodeRadius_)),
      score_(5u)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
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

    pickupBuffer_.loadFromFile("assets/sounds/pickup.wav");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    dieBuffer_.loadFromFile("assets/sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

void Snake::initNodes()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    path_.push_back(SnakePathNode(
        Game::VideoMode_.width / 2.0f,
        Game::VideoMode_.height / 2.0f));
    for (int i = 1; i <= 10 * InitialSize; i++)
    {
        path_.push_back(SnakePathNode(
            Game::VideoMode_.width / 2.0f,
            Game::VideoMode_.height / 2.0f + i * nodeRadius_ / 5.0));
    }
        
}

void Snake::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction_ = Direction(0, -1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction_ = Direction(0, 1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction_ = Direction(-1, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction_ = Direction(1, 0);
}

void Snake::update(sf::Time delta)
{
    move();
    checkOutOfWindow();
    checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit> &fruits)
{
    auto toRemove = fruits.end();

    for (auto i = fruits.begin(); i != fruits.end(); ++i)
    {
        if (dis(i->shape_.getPosition(), path_.front()) < nodeRadius_ + 5.0f)
            toRemove = i;
    }

    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        grow();
        score_++;
        fruits.erase(toRemove);
    }
}

void Snake::grow()
{
    tailOverlap_ += 10;
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
        tailOverlap_--;
    else
        path_.pop_back();
}

void Snake::checkSelfCollisions()
{
    SnakePathNode &head = path_.front();
    int count = 0;

    for (auto i = path_.begin(); i != path_.end(); i++, count++)
        if (count >= 30 && dis(head, *i) < 2.0f * nodeRadius_)
            hitSelf_ = true;
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

void Snake::NodeRender(SnakePathNode last, SnakePathNode now, SnakePathNode middle, sf::RenderWindow &window)
{
    nodeShape.setPosition(now);
    window.draw(nodeShape);

    nodeMiddle.setPosition(middle);
    sf::Vector2f recDirection(now - last);
    static sf::Vector2f vec2fZero = sf::Vector2f(0.f, 0.f);
    float angle = std::acos(recDirection.y / dis(recDirection, vec2fZero)) / 3.14159265358979323846 * 180.0;
    if (last.x >= now.x)
        nodeMiddle.setRotation(angle);
    else
        nodeMiddle.setRotation(-angle);
    window.draw(nodeMiddle);
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
    int count = 0;
    SnakePathNode lastSnakeNode, lastMiddleNode, nowSnakeNode;
    for (auto i = path_.begin(); i != path_.end(); i++, count++)
    {
        if (i == path_.begin())
        {
            // TODO 1: render snakehead
            lastSnakeNode = *i;
            nodeShape.setPosition(toWindow(lastSnakeNode));
            window.draw(nodeShape);
            continue;
        }
        if (count % 5 == 0)
        {
            if (count % 2)
                lastMiddleNode = *i;
            else
            {
                nowSnakeNode = *i;
                NodeRender(lastSnakeNode, nowSnakeNode, lastMiddleNode, window);
                if (nowSnakeNode.x < 0 || lastSnakeNode.x < 0)
                    NodeRender(toWindow(lastSnakeNode), toWindow(nowSnakeNode), toWindow(lastMiddleNode), window);
                if (nowSnakeNode.x > Game::VideoMode_.width || lastSnakeNode.x > Game::VideoMode_.width)
                    NodeRender(toWindow(lastSnakeNode), toWindow(nowSnakeNode), toWindow(lastMiddleNode), window);
                if (nowSnakeNode.y < 0 || lastSnakeNode.y < 0)
                    NodeRender(toWindow(lastSnakeNode), toWindow(nowSnakeNode), toWindow(lastMiddleNode), window);
                if (nowSnakeNode.y > Game::VideoMode_.height || lastSnakeNode.y > Game::VideoMode_.height)
                    NodeRender(toWindow(lastSnakeNode), toWindow(nowSnakeNode), toWindow(lastMiddleNode), window);
                lastSnakeNode = nowSnakeNode;
            }
        }
    }
}