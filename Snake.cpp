#include <SFML/Graphics.hpp>

#include "Snake.h"

using namespace sfSnake;

Snake::Snake()
{

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
	switch (direction_)
	{
	case Direction::Up:
		moveUp();
		break;
	case Direction::Down:
		moveDown();
		break;
	case Direction::Left:
		moveLeft();
		break;
	case Direction::Right:
		moveRight();
		break;
	}
}

void Snake::render(sf::RenderWindow& window)
{

}

void Snake::moveUp()
{
	
}

void Snake::moveDown()
{

}

void Snake::moveLeft()
{

}

void Snake::moveRight()
{

}