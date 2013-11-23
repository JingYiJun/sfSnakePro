#include <SFML/Graphics.hpp>

#include "Snake.h"
#include <iostream>

#include "Game.h"

using namespace sfSnake;

Snake::Snake() : direction_(Direction::Up)
{
	initNodes();
}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
	}
}

void Snake::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction_ = Direction::Up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction_ = Direction::Down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction_ = Direction::Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction_ = Direction::Right;
}

void Snake::update(sf::Time delta)
{
	move();
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	switch (direction_)
	{
	case Direction::Up:
		nodes_[0].move(0, -SnakeNode::Height);
		break;
	case Direction::Down:
		nodes_[0].move(0, SnakeNode::Height);
		break;
	case Direction::Left:
		nodes_[0].move(-SnakeNode::Width, 0);
		break;
	case Direction::Right:
		nodes_[0].move(SnakeNode::Width, 0);
		break;
	}
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window);
}